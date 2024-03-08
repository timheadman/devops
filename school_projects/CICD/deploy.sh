#!/bin/bash
scp src/cat/s21_cat gitlab-runner@10.1.1.2:~/
scp src/grep/s21_grep gitlab-runner@10.1.1.2:~/
ssh gitlab-runner@10.1.1.2 "mv s21_cat s21_grep /usr/local/bin"