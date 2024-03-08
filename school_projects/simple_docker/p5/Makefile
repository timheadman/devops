.PHONY: build stop clean check
build: stop clean
	docker build -t s21_server_p5:v1.0 .

run: 
	docker run --rm --publish 80:81 --volume  \
				./nginx/:/etc/nginx \
				--name=s21_server_p5 \
				s21_server_p5:v1.0 

stop:
	docker container stop s21_server_p5

check: build 
	sudo dockle s21_server_p5:v1.0

clean:
	docker container stop s21_server_p5; \
	docker container rm s21_server_p5


