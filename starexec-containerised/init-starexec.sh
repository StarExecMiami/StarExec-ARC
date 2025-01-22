#!/bin/bash

function cleanup() {
    echo 'Container stopped, performing cleanup...'
    /project/apache-tomcat-7/bin/shutdown.sh
    /usr/bin/mysqladmin -u root shutdown
    /usr/sbin/apache2ctl -k graceful-stop
    exit 0
}

trap cleanup SIGINT SIGTERM

set -e
set -o pipefail

# Configurar permisos
chown -R tomcat:star-web /project
chown -R tomcat:star-web /home/starexec
chown -R tomcat:star-web /home/sandbox
chown -R mysql:mysql /var/lib/mysql
chmod 755 -R /home/starexec

# Iniciar Apache2
/usr/sbin/apache2ctl -D FOREGROUND &

# Iniciar MySQL
/usr/bin/mysqld_safe --basedir=/usr --user=mysql &

# Esperar a que MySQL inicie
until mysqladmin ping &>/dev/null; do
    echo "Esperando a que MySQL inicie..."
    sleep 1
done

# Configurar base de datos
mysql -u root -e "
    DROP DATABASE IF EXISTS $DB_NAME;
    CREATE DATABASE $DB_NAME;
    GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';
    FLUSH PRIVILEGES;
"

# Configurar conexión Podman
echo "Configurando conexión Podman"
podman system connection add host-machine-podman-connection \
    ssh://${SSH_USERNAME}@${HOST_MACHINE}:${SSH_PORT}${SOCKET_PATH} \
    --identity=/root/.ssh/starexec_podman_key || echo "Falló la configuración de la conexión Podman"

# Iniciar Tomcat
/project/apache-tomcat-7/bin/catalina.sh run &

# Esperar a que Tomcat inicie
until curl -s http://localhost:8080 >/dev/null; do
    echo "Esperando a que Tomcat inicie..."
    sleep 1
done

# Despliegue suave de StarExec
cd $DEPLOY_DIR
echo "Ejecutando ant build -buildfile $BUILD_FILE reload-sql update-sql"
if ! ant build -buildfile $BUILD_FILE reload-sql update-sql; then
    echo "Ejecutando NewInstall.sql"
    cd $DEPLOY_DIR/sql && mysql -u root $DB_NAME < $SQL_FILE
    cd $DEPLOY_DIR

    if ! ant build -buildfile $BUILD_FILE reload-sql update-sql; then
        echo "ERROR! Por favor, vuelva a ejecutar docker build..."
        exit 1
    fi
fi

script/soft-deploy.sh && printf "¡ÉXITO! ACCEDE EN TU NAVEGADOR A: http://localhost \n\nusuario: admin \ncontraseña: admin\n\n"

# Mantener el contenedor en ejecución
tail -f /dev/null
