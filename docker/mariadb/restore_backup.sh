#!/bin/bash

echo "!!! FIRST DELETE CONTAINER DATA !!!\nsudo rm -r /var/lib/docker/volumes/mariadb_mysql/_data/*"

docker compose down
#rm -rf --verbose ~/scripts/docker/mariadb/backup
#rsync -az --verbose tim@10.11.12.250:/volume1/netbackup/mariadb/backup .


docker run --user root --rm -v mariadb_mysql:/var/lib/mysql -v mariadb_backup:/backup mariadb:latest mariabackup --copy-back --target-dir=/backup
