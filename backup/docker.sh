#!/bin/bash

if ! command -v jq &> /dev/null; then
    echo "Install jq first. (sudo apt install jq)"
    exit 1
fi

if [[ "$#" == 0 ]]; then
    echo Requires at least 1 container name.
    exit 1
fi

date_tag=$(date +%Y%m%dT%H%M%S)
destination_folder="/mnt/hdd/backup"
remote_server=nas
remote_name=$(whoami)
remote_folder=/volume1/netbackup/$(hostname)/docker

echo "##############################"
echo "#   DOCKER CONTAINER BACKUP  #"
echo "##############################"
echo Remote server: $remote_server
echo Remote user: $remote_name
echo Remote dir: $remote_folder
echo Temporary dir: $destination_folder
echo "##############################"

# mkdir -p ${destination_folder}
# ssh $remote_name@$remote_server "mkdir -p $remote_folder"

backup_volumes(){
    paths=""
    container_name=$1
    file_name=${container_name}_${date_tag}.tar.bz2

    path_list=($(docker inspect ${container_name} | jq '.[] | .Mounts[].Destination'))
    
    if [ -z ${path_list+x} ]; then
        echo "The container is not running or does not exist."
	exit 1
    fi

    for i in $(seq ${#path_list[@]}); do
        path=$(echo ${path_list[i-1]} | tr -d '"')
        paths="${paths} ${path}"
    done
  
    echo "* Container: ${container_name}, file: ${file_name}, paths: ${paths}"

    docker run --rm --volumes-from ${container_name} --volume ${destination_folder}:/tmp busybox \
    sh -c "tar --create --bzip2 --file=/tmp/${file_name} ${paths} && \
    adduser -D ${USER} && \
    chown -R ${USER}:${USER} /tmp && \
    chmod 755 /tmp"
}


start_timestamp=$(date +%s)

for arg in $*; do
    backup_volumes ${arg}
done

end_timestamp=$(date +%s)
diff_timestamp=$((end_timestamp - start_timestamp))

echo -e "$date_tag [$diff_timestamp] $1" >> $destination_folder/docker_sh.log

echo "##############################"
echo Execution time: $diff_timestamp s.
echo "##############################"

ls -l --human-readable --sort=time ${destination_folder}


##############################
#            END             #
##############################
# scp ${destination_folder}/* $remote_name@$remote_server:$remote_folder 
# rm -rf ${destination_folder}

