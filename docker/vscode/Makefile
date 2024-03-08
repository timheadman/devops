.PHONY: build clean run restart
build: clean
	docker compose build nginx

down:
	@echo "\n----- CONTAINERS -----"
	@docker container list --all
	@echo "\n----------------------"
	docker compose down
	@echo "\n----- CONTAINERS -----"
	@docker container list --all
	@echo "\n------- IMAGES -------"
	@docker images --all
	@echo "\n------ VOLUMES ------"
	@docker volume ls
	@echo "\n------ NETWORKS ------"
	@docker network ls

up:
	docker compose up --detach
	@echo "\n----- CONTAINERS -----"
	@docker container list --all
	@echo "\n------ VOLUMES ------"
	@docker volume ls
	@echo "\n------ NETWORKS ------"
	@docker network ls
	@echo "\n----------------------"

restart:
	docker compose down
	docker compose up --detach

