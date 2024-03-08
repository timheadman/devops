#!/bin/bash

date_tag=$(date +%Y%m%dT%H%M%S)
script_name=$0
script_name=${script_name%.sh}
script_name=${script_name##*/}

remote_server=nas
remote_name=$(whoami)
remote_folder=/volume1/netbackup/$(hostname)/${script_name}
temp_in_folder="$(pwd)/temp_in_${date_tag}"
temp_out_folder="$(pwd)/temp_out_${date_tag}"
archive_name=${script_name}-${date_tag}.tar.bz2

echo "##############################"
echo "#           BACKUP           #"
echo "##############################"
echo Remote server: $remote_server
echo Remote user: $remote_name
echo Remote folder: $remote_folder
echo Temp IN folder: $temp_in_folder
echo Temp OUT folder: $temp_out_folder
echo File: $archive_name
echo "##############################"

# Prepare local and remote folders.
mkdir -p ${temp_in_folder} ${temp_out_folder}
ssh $remote_name@$remote_server "mkdir -p $remote_folder"

# Save configs to temp_in_folder
guake --save-preferences ${temp_in_folder}/guake-manual
cp ~/.vimrc ${temp_in_folder}/

# Make files.
tar --create --auto-compress --file=$temp_out_folder/$archive_name --directory=$temp_in_folder .

# Copy to destination all files from temp_out_folder.
scp ${temp_out_folder}/* $remote_name@$remote_server:$remote_folder

# Remove temporary.
rm -rf ${temp_in_folder} ${temp_out_folder}

