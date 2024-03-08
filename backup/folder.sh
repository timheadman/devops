#!/bin/bash

if [[ "$#" == 0 ]]; then
    echo Requires at least 1 folder name.
    exit 1
fi

date_tag=$(date +%Y%m%dT%H%M%S)
destination_folder="/mnt/hdd/backup"
remote_server=10.11.12.200
remote_name=$(whoami)
remote_folder=/volume1/netbackup/$(hostname)/folders

backup_folder() {
    date_tag=$(date +%Y%m%dT%H%M%S)
    target_folder=$1
    destination_file_name=${1/\//}
    destination_file_name=${destination_file_name//\//_}_${date_tag}.tar.bz2

    echo "##############################"
    echo "#        FOLDER BACKUP       #"
    echo "##############################"
    echo Target folder: $target_folder
    echo Destination folder: $destination_folder
    echo Destination file: $destination_file_name
    echo Remote server: $remote_server
    echo Remote user: $remote_name
    echo Remote folder: $remote_folder
    echo "##############################"

    start_timestamp=$(date +%s)

    if [ "$1" = "root" ]; then
        nice -n 10 tar --create --acls --use-compress-program=pbzip2 \
                       --file=$destination_folder/$destination_file_name \
                       --exclude=/home --exclude=/media --exclude=/dev \
                       --exclude=/mnt --exclude=/proc --exclude=/sys \
                       --exclude=/tmp --exclude=/var/lib/docker/volumes/samba/_data \
                       /
    else
        nice -n 10 tar --create --acls --use-compress-program=pbzip2 \
                       --file=$destination_folder/$destination_file_name \
                       /${target_folder}
    fi

    end_timestamp=$(date +%s)
    diff_timestamp=$((end_timestamp - start_timestamp))
    
    echo -e "$date_tag [$diff_timestamp] $destination_file_name" >> $destination_folder/folder_sh.log
    
    echo "##############################"
    echo Execution time: $diff_timestamp s.
    echo "##############################"

}

# Prepare local folder.
# mkdir --parents --verbose ${destination_folder}

# For each folders
for arg in $*; do
    backup_folder ${arg}
done

# if [ -z "$(ls -A ${destination_folder})" ]; then
#    echo -e "\nDestination folder is empty. Somthing wrong. Remove folder.\n"
# else
#    echo -e "\nDone.\n"
# fi

# Remote backup.
# ssh $remote_name@$remote_server "mkdir -p $remote_folder"
# scp ${destination_folder}/* $remote_name@$remote_server:$remote_folder
# rm -rf ${destination_folder}
