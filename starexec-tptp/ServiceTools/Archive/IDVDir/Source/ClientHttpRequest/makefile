
default: ClientHttpRequest.jar

ClientHttpRequest.jar : ClientHttpRequest.class
	jar cf ClientHttpRequest.jar ClientHttpRequest/ClientHttpRequest.class ClientHttpRequest/ClientHttpRequest.java

ClientHttpRequest.class: ClientHttpRequest/ClientHttpRequest.java
	javac -source 1.5 -target 1.5 ClientHttpRequest/ClientHttpRequest.java

clean:
	rm -rf ClientHttpRequest/*.class ClientHttpRequest.jar
