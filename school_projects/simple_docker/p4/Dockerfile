FROM nginx:latest

ENV WORKDIR=/home

WORKDIR ${WORKDIR}

COPY  ./s21_server.c s21_server.c
COPY ./entrypoint.sh entrypoint.sh
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

RUN apt update; \
    apt install -y nginx gcc spawn-fcgi libfcgi-dev; \
    chmod +x /home/entrypoint.sh; 

ENTRYPOINT ["/home/entrypoint.sh"]


