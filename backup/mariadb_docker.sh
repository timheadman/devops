#!/bin/bash

docker run --name mariadb_backup_socket -v mariadb_mysql:/var/lib/mysql -v mariadb_backup_socket:/var/run/mysqld -e MARIADB_MYSQL_LOCALHOST_USER=1 -e MARIADB_MYSQL_LOCALHOST_GRANTS="RELOAD, PROCESS, LOCK TABLES, BINLOG MONITOR" -e MARIADB_ROOT_PASSWORD=pcIv8hOpNdwl -d mariadb:10.11.2

docker run --rm --name mariadb_backup -v mariadb_backup:/backup mariadb:10.11.2 chown mysql: /backup

docker run --user mysql -v mariadb_backup_socket:/var/run/mysqld -v mariadb_backup:/backup -v mariadb_mysql:/var/lib/mysql --rm mariadb:10.11.2 mariabackup --backup --target-dir=/backup
