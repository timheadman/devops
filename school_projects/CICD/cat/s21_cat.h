// Copyright [2023] <phyliscr>

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include "../common/options.h"

typedef struct {
  int A;  // -A, --show-all, equivalent to -vET
  int b;  // -b, --number-nonblank, number nonempty
          // output lines, overrides -n
  int e;  // -e, equivalent to -vE
  int E;  // -E, --show-ends, display $ at end of each line
  int n;  // -n, --number, number all output lines
  int s;  // -s, --squeeze-blank, suppress repeated empty output
  int t;  // -t, equivalent to -vT
  int T;  // -T, --show-tabs, display TAB characters as ^I
  int v;  //  -v, --show-nonprinting, use ^ and M- notation, except
          //  for LFD and TAB
} Options;

int main(int argc, char const *argv[]);
void init_options(Options *options);
int switch_options(const char *value, Options *options);
int parse_options(Files *files, Options *options, int argc, char const *argv[]);

void open_file(Files *files, Options *options, int *row_count);
void print_number(int *new_row, int *row_count);
void show_nonprinting(unsigned char ascii);

#endif
