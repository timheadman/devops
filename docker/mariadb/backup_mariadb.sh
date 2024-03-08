#!/bin/bash

echo MariaDB root password:
read root_pswd

cd mariadb_bins_link

echo Sudo password:
sudo rm -r /volume1/netbackup/mariadb/backup/*
sudo ./mariabackup --backup --target-dir=/volume1/netbackup/mariadb/backup/ --user=root --password=$root_pswd
sudo ./mariabackup --prepare --target-dir=/volume1/netbackup/mariadb/backup

cd ~

