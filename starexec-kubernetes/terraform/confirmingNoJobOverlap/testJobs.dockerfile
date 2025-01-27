FROM python:3

WORKDIR /usr/src/app
COPY entrypoint.py ./
ENTRYPOINT [ "python", "entrypoint.py" ]

