FROM nginx

RUN apt update
RUN apt install -y certbot python3-certbot-nginx cron

ENV TZ=Europe/Moscow

COPY cronfile /cron.d
RUN chmod 0644 /cron.d/cronfile

COPY certbot.sh /cron.d
RUN chmod 0755 /cron.d/certbot.sh

