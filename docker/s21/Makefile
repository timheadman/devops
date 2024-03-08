## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##
## @copyright Copyright [2023] <Phylis Cristobal>  ##
## @file Makefile                                  ##
## @date 2023-09-13                                ##
## @author Phylis Cristobal (phyliscr)             ##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##

CONTAINER := s21_postgre
VOLUME := $(shell docker inspect --format='{{range .Mounts}}{{.Name}}{{end}}' $(CONTAINER))
PASSWORD := $(shell cat secret.cfg)

.PHONY: list new prune

list:
	@-docker container ls --filter='name=$(CONTAINER)' 
	@echo VOLUME: $(VOLUME)

new:
	@-docker run --name $(CONTAINER) -e POSTGRES_PASSWORD=$(PASSWORD) -d -p 21000:5432 postgres

prune: list
	@-docker stop $(CONTAINER) 
	@-docker container rm $(CONTAINER)
	@-docker volume rm $(VOLUME)
