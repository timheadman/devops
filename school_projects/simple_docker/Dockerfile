FROM debian:stable-20230522-slim

ENV WORKDIR=/home
ENV USER=nginx

WORKDIR ${WORKDIR}

COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./server/s21_server.c s21_server.c
COPY ./entrypoint.sh entrypoint.sh

RUN useradd -d ${WORKDIR} -m -s /bin/bash ${USER}; \
    apt update; \
    apt install -y nginx gcc spawn-fcgi libfcgi-dev; \
    apt clean; \
    rm -rf /var/lib/apt/lists/*; \
    chmod u-s /usr/bin/gpasswd; \
    chmod u-s /usr/bin/newgrp; \
    chmod u-s /bin/su; \
    chmod u-s /bin/mount; \
    chmod u-s /bin/umount; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/chsh; \
    chmod g-s /usr/bin/expiry; \
    chmod g-s /usr/bin/wall; \
    chmod g-s /sbin/unix_chkpwd; \
    chmod g-s /usr/bin/chage; \
    chmod 755 /usr/bin/passwd; \
    chmod +x /home/entrypoint.sh

HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl -f http://localhost/ || exit 1

ENTRYPOINT ["/home/entrypoint.sh"]
