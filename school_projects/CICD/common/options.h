// Copyright [2023] <phyliscr>

#ifndef SRC_COMMON_OPTIONS_H_
#define SRC_COMMON_OPTIONS_H_

typedef struct Patterns {
  int count;
  char **pattern;
} Patterns;

typedef struct Files {
  int count;
  char **name;
} Files;

void add_pattern(Patterns *patterns, const char *value);
void add_filename(Files *files, const char *value);
void free_patterns(Patterns *patterns);
void free_files(Files *files);

#endif  // SRC_COMMONS_OPTION_H_