// Copyright [2023] <phyliscr>

#include "s21_grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
  int error_flag = 0;

  if (argc > 1) {
    Files files;
    Patterns patterns;
    Options options;
    files.count = 0;
    files.name = NULL;
    patterns.count = 0;
    patterns.pattern = NULL;
    init_options(&options);

    error_flag = parse_options(&patterns, &files, &options, argc, argv);

#ifdef DEBUG
    printf("patterns: ");
    for (int i = 0; i < patterns.count; i++) {
      printf("[%i]:%s", i, patterns.pattern[i]);
      i == patterns.count - 1 ? printf("\n") : printf(" ");
    }
    printf("files: ");
    for (int i = 0; i < files.count; i++) {
      printf("[%i]:%s", i, files.name[i]);
      i == files.count - 1 ? printf("\n") : printf(" ");
    }
#endif

    if (files.count && !error_flag) process_files(&patterns, &files, &options);

    free_patterns(&patterns);
    free_files(&files);
  }

  return error_flag;
}

void init_options(Options *options) {
  options->e = 0;  // -e
  options->i = 0;  // -i, --ignore-case
  options->v = 0;  // -v, --invert-match
  options->c = 0;  //  -c, --count
  options->l = 0;  // -l, --files-with-matches
  options->n = 0;  // -n, --line-number
  options->h = 0;  // -h, --no-filename
  options->s = 0;  // -s, --no-messages
  options->o = 0;  // -o, --only-matching
  options->f = 0;  // -f
}

int switch_options(const char *option, Options *options) {
  int error_flag = 0;
  if (!strcmp(option, "e")) {
  } else if (!strcmp(option, "i") || !strcmp(option, "ignore-case")) {
    options->i = 1;
  } else if (!strcmp(option, "v") || !strcmp(option, "invert-match")) {
    options->v = 1;
  } else if (!strcmp(option, "c") || !strcmp(option, "count")) {
    options->c = 1;
  } else if (!strcmp(option, "l") || !strcmp(option, "files-with-matches")) {
    options->l = 1;
  } else if (!strcmp(option, "n") || !strcmp(option, "line-number")) {
    options->n = 1;
  } else if (!strcmp(option, "h") || !strcmp(option, "no-filename")) {
    options->h = 1;
  } else if (!strcmp(option, "s") || !strcmp(option, "no-messages")) {
    options->s = 1;
  } else if (!strcmp(option, "o") || !strcmp(option, "only-matching")) {
    options->o = 1;
  } else if (!strcmp(option, "f") || !strcmp(option, "file")) {
    options->f = 1;
  } else {
    fprintf(stderr,
            "s21_grep: unrecognized option -- '%s'\n"
            "Usage: s21_grep [OPTION]... PATTERNS [FILE]...\n"
            "Try 's21_grep --help' for more information.\n",
            option);
    error_flag = 1;
  }
  return error_flag;
}

void e_argument(Patterns *patterns, int argc, char const *argv[], int *index) {
  for (int j = 1; j < (int)strlen(argv[*index]); j++) {
    if (argv[*index][j] == 'e') {
      const char *argument;
      if (j == (int)strlen(argv[*index]) - 1) {
        if (*index < argc - 1) {
          argument = argv[*index + 1];
          (*index)++;
        } else {
          argument = "";
        }
      } else {
        argument = argv[*index] + j + 1;
      }
      add_pattern(patterns, argument);
      break;
    }
  }
}

void f_argument(Patterns *patterns, Options *options, int argc,
                char const *argv[], int *index) {
  for (int j = 1; j < (int)strlen(argv[*index]); j++) {
    if (argv[*index][j] == 'f') {
      const char *argument;
      if (j == (int)strlen(argv[*index]) - 1) {
        if (*index < argc - 1) {
          argument = argv[*index + 1];
          (*index)++;
        } else {
          argument = "";
        }
      } else {
        argument = argv[*index] + j + 1;
      }
      strcpy(options->regex_file, argument);
      FILE *file_pointer;
      if ((file_pointer = fopen(options->regex_file, "r")) == NULL) {
        if (!options->s) fprintf(stderr, "s21_grep: No such file or directory");
      } else {
        char buffer[BUFFER_SIZE];

        while (!feof(file_pointer)) {
          if (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
            add_pattern(patterns, buffer);
        }
        fclose(file_pointer);
      }
      break;
    }
  }
}

int parse_options(Patterns *patterns, Files *files, Options *options, int argc,
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
          if (argv[i][j] == 'e') {
            e_argument(patterns, argc, argv, &i);
            break;
          } else if (argv[i][j] == 'f') {
            f_argument(patterns, options, argc, argv, &i);
            break;
          } else {
            char tmp_string[2] = {argv[i][j], '\0'};
            error_flag = switch_options(tmp_string, options);
            if (error_flag) break;
          }
        }
      }
    } else if (!patterns->count) {
      add_pattern(patterns, argv[i]);
    } else {
      add_filename(files, argv[i]);
    }
  }
  return error_flag;
}

int process_files(Patterns *patterns, Files *files, Options *options) {
  int error_flag = 0;
  for (int i = 0; i < files->count; i++) {
    FILE *file_pointer;
    int match_counter = 0;
    if ((file_pointer = fopen(files->name[i], "r")) == NULL) {
      if (!options->s)
        fprintf(stderr, "s21_grep: %s: No such file or directory",
                files->name[i]);
    } else {
      char buffer[BUFFER_SIZE];
      int row_buffer_size = 1;  // End of string symbol
      char *row_buffer = NULL;
      char *realloc_temp;

      int row_count = 0;

      while (!feof(file_pointer)) {
        if (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
          row_buffer_size = row_buffer_size + strlen(buffer);
          if (row_buffer_size == (int)strlen(buffer) + 1)
            realloc_temp = calloc(sizeof(char), row_buffer_size);
          else
            realloc_temp = realloc(row_buffer, sizeof(char) * row_buffer_size);
          if (realloc_temp != NULL) {
            row_buffer = realloc_temp;
          } else {
            fprintf(stderr, "s21_grep: Memory allocation error");
            free(row_buffer);
            error_flag = 1;
          }
          strcat(row_buffer, buffer);
          if (strlen(buffer) != BUFFER_SIZE - 1) {  // End of string
            row_count++;
            match_counter += process_string(row_buffer, row_count, patterns,
                                            files, options, i);
            free(row_buffer);
            row_buffer_size = 1;
          }
        }
      }
      fclose(file_pointer);
    }
    if (error_flag) break;
    if (match_counter) {
      if (options->c) {
        if (files->count > 1)
          printf("%s:%i\n", files->name[i], match_counter);
        else
          printf("%i\n", match_counter);
      }
      if (options->l) printf("%s\n", files->name[i]);
    }
  }
  return error_flag;
}

// make check ARGS="-e It -e of -o ../../data-samples/test1
// ../../data-samples/test2"; grep -e It -e of -o ../../data-samples/test1
// ../../data-samples/test2

int process_string(char *string, int row_count, Patterns *patterns,
                   Files *files, Options *options, int file_index) {
  int is_match = 0;
  int error_flag = 0;
  int buffer_size = strlen(string) + 1;
  char *print_buffer = calloc(sizeof(char), buffer_size);
  strcpy(print_buffer, string);

  for (int j = 0; j < patterns->count; j++) {
    regex_t regex;
    int reti;
    if (options->i)  // -i, --ignore-case
      reti = regcomp(&regex, patterns->pattern[j], REG_ICASE);
    else
      reti = regcomp(&regex, patterns->pattern[j], 0);

    if (reti) {
      fprintf(stderr, "s21_grep: Invalid regular expression");
      error_flag = 1;
      break;
    }
    char *buffer = calloc(sizeof(char), buffer_size);
    strcpy(buffer, print_buffer);

    char *start_position = buffer;
    int eos = 0;
    print_buffer[0] = '\0';
    while (!eos) {
      regmatch_t match;
      if ((reti = regexec(&regex, start_position, 1, &match, 0)) ==
          REG_NOMATCH) {
        strcat(print_buffer, start_position);
        eos = 1;
      } else {
        is_match = 1;
        buffer_size = buffer_size + strlen(patterns->pattern[j]);
        char *realloc_temp = realloc(print_buffer, buffer_size);
        if (realloc_temp != NULL) {
          print_buffer = realloc_temp;
        } else {
          fprintf(stderr, "s21_grep: Memory allocation error");
          error_flag = 0;
          break;
        }
        strncat(print_buffer, start_position, match.rm_eo);
        start_position += match.rm_eo;
        if (options->o)  // -o, --only-matching
          print_string(patterns->pattern[j], options, row_count, is_match,
                       files, file_index);
      }
    }
    regfree(&regex);
    free(buffer);
  }
  if (!error_flag && !options->o)  // !NO! -o, --only-matching
    print_string(print_buffer, options, row_count, is_match, files, file_index);
  else
    is_match = -1;
  free(print_buffer);
  return is_match;
}

void print_string(char *print_buffer, Options *options, int row_count,
                  int is_match, Files *files, int file_index) {
  if (options->v) is_match = !is_match;  // -v, --invert-match
  //  -c, --count, -l, --files-with-matches
  if (is_match) {
    if (!options->c &&
        !options->l) {  // !NO! -v, --invert-match && !NO! -c, --count
      if (files->count > 1 && !options->h)
        printf("%s:", files->name[file_index]);
      if (options->n) printf("%i:", row_count);  // -n, --line-number
      if (options->o)                            // -o, --only-matching
        printf("%s\n", print_buffer);
      else
        printf("%s", print_buffer);
    }
  }
}
