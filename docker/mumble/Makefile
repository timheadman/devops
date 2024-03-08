## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
##                   VARIABLES                     ## 
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
CONTAINER := mumble
VOLUME := $(shell docker inspect --format='{{range .Mounts}}{{.Name}}{{end}}' $(CONTAINER))

IMAGE := $(CONTAINER)
IMAGE_TAG := $(shell grep 'ARG MUMBLE_VERSION' Dockerfile | awk -F = '{print $$2}')

## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
##                    COMMANDS                     ##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
.PHONY: run superuser list prune

run:
	docker compose up --detach --build

superuser:
	 docker exec -it mumble supw

list:
	@echo "CONTAINER: $(CONTAINER), IMAGE: $(IMAGE):$(IMAGE_TAG), VOLUME: $(VOLUME)" 
	-docker container ls --filter='name=$(CONTAINER)' 

prune: list
	-docker compose down
	-docker volume rm $(VOLUME)	
	-docker image rm --force $(IMAGE):$(IMAGE_TAG)
