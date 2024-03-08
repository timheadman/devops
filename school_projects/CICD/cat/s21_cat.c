#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/options.h"

#define BUFFER_SIZE 1024
#define OPTIONS_QUANTITY 6

int main(int argc, char const *argv[]) {
  int error_flag = 0;
  int row_count = 0;

  if (argc > 1) {
    Files files;
    Options options;
    files.count = 0;
    files.name = NULL;
    init_options(&options);

    error_flag = parse_options(&files, &options, argc, argv);

#ifdef DEBUG
    for (int i = 0; i < files.count; i++)
      printf("files[%i]:%s\n", i, files.name[i]);
#endif

    if (!error_flag) open_file(&files, &options, &row_count);

    free_files(&files);
  }

  return error_flag;
}

void init_options(Options *options) {
  options->b = 0;
  options->E = 0;
  options->n = 0;
  options->s = 0;
  options->T = 0;
  options->v = 0;
}

int switch_options(const char *option, Options *options) {
#ifdef DEBUG
  printf("[so:%s] ", option);
#endif
  int error_flag = 0;
  if (!strcmp(option, "A") || !strcmp(option, "show-all")) {
    options->v = 1;
    options->E = 1;  // options->E = 1;
    options->T = 1;
  } else if (!strcmp(option, "b") || !strcmp(option, "number-nonblank")) {
    options->b = 1;
  } else if (!strcmp(option, "e")) {
    options->v = 1;
    options->E = 1;
  } else if (!strcmp(option, "E") || !strcmp(option, "show-ends")) {
    options->E = 1;
  } else if (!strcmp(option, "n") || !strcmp(option, "number")) {
    options->n = 1;
  } else if (!strcmp(option, "s") || !strcmp(option, "squeeze-blank")) {
    options->s = 1;
  } else if (!strcmp(option, "t")) {
    options->v = 1;
    options->T = 1;
  } else if (!strcmp(option, "T") || !strcmp(option, "show-tabs")) {
    options->T = 1;
  } else if (!strcmp(option, "v") || !strcmp(option, "show-nonprinting")) {
    options->v = 1;
  } else {
    fprintf(stderr, "s21_cat: invalid option -- '%s'\n", option);
    error_flag = 1;
  }
  return error_flag;
}

int parse_options(Files *files, Options *options, int argc,
                  char const *argv[]) {
  int error_flag = 0;
  for (int i = 1; i < argc; i++) {
#ifdef DEBUG
    printf("[%i/%i:%s]", i, argc - 1, argv[i]);
    i == argc - 1 ? printf("\n") : printf(" ");
#endif
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        error_flag = switch_options(argv[i] + 2, options);
        if (error_flag) break;
      } else {  // short may be multiple
        for (int j = 1; j < (int)strlen(argv[i]); j++) {
          char tmp_string[2] = {argv[i][j], '\0'};
          error_flag = switch_options(tmp_string, options);
          if (error_flag) break;
        }
      }
    } else {
      add_filename(files, argv[i]);
    }
  }
  return error_flag;
}

void open_file(Files *files, Options *options, int *row_count) {
  for (int i = 0; i < files->count; i++) {
    FILE *file_pointer;
    if ((file_pointer = fopen(files->name[i], "r")) == NULL) {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n",
              files->name[i]);
    } else {
      char buffer[BUFFER_SIZE];
      int new_row = 1;
      int blank_row = 0;
      while (!feof(file_pointer)) {
        if (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
          if (strlen(buffer) == 1 && options->s == 1)  // -s
            if (blank_row == 0)
              blank_row = 1;
            else
              continue;
          else
            blank_row = 0;
          if (new_row == 1) {
            if ((options->b == 1 && strlen(buffer) != 1) ||
                (options->n == 1 && options->b != 1))  // -b && -n
              print_number(&new_row, row_count);
          }
          for (size_t j = 0; j < strlen(buffer); j++) {
            if (buffer[j] == 10) {
              new_row = 1;
              if (options->E == 1) printf("$");  // -E
            }
            if (buffer[j] == 9 && options->T == 1)
              printf("^I");  // -T
            else {
              if (options->v == 1)
                show_nonprinting((unsigned char)buffer[j]);  // -v
              else
                printf("%c", buffer[j]);
            }
          }
        }
      }
      fclose(file_pointer);
    }
  }
}

void print_number(int *new_row, int *row_count) {
  *new_row = 0;
  ++(*row_count);
  int num_space = 5;
  if (*row_count >= 10) num_space = 4;
  if (*row_count >= 100) num_space = 3;
  if (*row_count >= 1000) num_space = 2;
  if (*row_count >= 10000) num_space = 1;
  printf("%*c", num_space, ' ');
  printf("%i\t", *row_count);
}

void show_nonprinting(unsigned char ascii) {
  if ((ascii <= 8) || (ascii >= 11 && ascii <= 31))
    printf("^%c", ascii + 64);
  else if (ascii >= 128)
    printf("M-^%c", ascii - 64);
  else
    printf("%c", ascii);
}