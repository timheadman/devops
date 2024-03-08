// Copyright [2023] <phyliscr>

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include "../common/options.h"

typedef struct {
  int e;  // -e, --regexp=PATTERNS
  int i;  // -i, --ignore-case
  int v;  // -v, --invert-match
  int c;  //  -c, --count
  int l;  // -l, --files-with-matches
  int n;  // -n, --line-number
  int h;  // -h, --no-filename
  int s;  // -s, --no-messages
  int o;  // -o, --only-matching
  int f;  // -f, --file=FILE
  char regex_file[256];
} Options;

int main(int argc, char const *argv[]);
void init_options(Options *options);
int switch_options(const char *value, Options *options);
int parse_options(Patterns *patterns, Files *files, Options *options, int argc,
                  char const *argv[]);

int process_files(Patterns *patterns, Files *files, Options *options);
int process_string(char *string, int row_count, Patterns *patterns,
                   Files *files, Options *options, int file_index);

void print_string(char *print_buffer, Options *options, int row_count,
                  int is_match, Files *files, int file_index);
void e_argument(Patterns *patterns, int argc, char const *argv[], int *index);

#endif  // SRC_GREP_S21_GREP_H_
