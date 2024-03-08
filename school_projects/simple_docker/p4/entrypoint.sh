#!/usr/bin/env bash

gcc s21_server.c -o s21_server.fcgi -lfcgi
spawn-fcgi -p 8080 ./s21_server.fcgi
nginx -g "daemon off;"
