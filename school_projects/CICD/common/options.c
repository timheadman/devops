#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_pattern(Patterns *patterns, const char *value) {
  patterns->pattern =
      realloc(patterns->pattern, sizeof(char *) * (patterns->count + 1));
  patterns->pattern[patterns->count] = calloc(sizeof(char), strlen(value) + 1);
  strcpy(patterns->pattern[patterns->count], value);
  patterns->count++;
}

void add_filename(Files *files, const char *value) {
  files->name = realloc(files->name, sizeof(char *) * (files->count + 1));
  files->name[files->count] = calloc(sizeof(char), strlen(value) + 1);
  strcpy(files->name[files->count], value);
  files->count++;
}

void free_patterns(Patterns *patterns) {
  for (int i = 0; i < patterns->count; i++) free(patterns->pattern[i]);
  free(patterns->pattern);
}

void free_files(Files *files) {
  for (int i = 0; i < files->count; i++) free(files->name[i]);
  free(files->name);
}
