CONTAINER := dlna
VOLUME := $(shell docker inspect --format='{{range .Mounts}}{{.Name}}{{end}}' $(CONTAINER))
PASSWORD := $(shell cat secret.cfg)

.PHONY: list run prune

list:
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LIST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@-docker container ls --filter='name=$(CONTAINER)' 
	@echo ----------------------------------------------------------------------
	@echo VOLUME: $(VOLUME)
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

run:
	@docker run -d \
				--name=$(CONTAINER) \
				--restart=always \
				--net=host \
  				-v /mnt/hdd/samba/video:/media \
  				-e TZ=Europe/Moscow \
  				-e MINIDLNA_MEDIA_DIR=/media \
  				-e MINIDLNA_FRIENDLY_NAME=Server_DLNA \
  				vladgh/minidlna

prune: list
	@-docker stop $(CONTAINER) 
	@-docker container rm $(CONTAINER)
