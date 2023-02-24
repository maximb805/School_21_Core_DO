#ifndef S21_GREP_H
#define S21_GREP_H
#define MAX_COUNT 50
#define MAX_PATT_LEN 4096

#include <regex.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

char *get_pattern(struct flags flags, int argc, char **argv,
                  int *pattern_index);
int check_flags(struct flags *flags, int argc, char **argv,
                int *e_pattern_count, int *f_pattern_count,
                char e_patterns_arr[][MAX_PATT_LEN],
                char f_patterns_arr[][MAX_PATT_LEN]);
void fill_patterns_arrs(int argc, char **argv, int *e_pattern_count,
                        int *f_pattern_count,
                        char e_patterns_arr[][MAX_PATT_LEN],
                        char f_patterns_arr[][MAX_PATT_LEN]);
int add_pattern(int arg_num, char **argv, int *pattern_num,
                int patt_first_symbol_index, char patterns_arr[][MAX_PATT_LEN]);
int main_printer(struct flags flags, int argc, char **argv, int e_pattern_count,
                 char e_patterns_arr[][MAX_PATT_LEN], int f_pattern_count,
                 char f_patterns_arr[][MAX_PATT_LEN]);
int get_file_index(int argc, char **argv);
int check_f_files(int f_pattern_count, char f_patterns_arr[][MAX_PATT_LEN]);
void delete_nextline(char *pattern_file_string);
void check_last_symbol(char *file_string);
int flag_o_printer(struct flags flags, int argc, char **argv,
                   int e_pattern_count, char e_patterns_arr[][MAX_PATT_LEN],
                   int f_pattern_count, char f_patterns_arr[][MAX_PATT_LEN]);
char *change_indexes(char *temp_string, size_t pmatch_elems, regmatch_t *pmatch,
                     int is_new_arg);
void sort_pmatch(size_t pmatch_elems, regmatch_t *pmatch);
void print_matches(struct flags flags, char *temp_string, size_t pmatch_elems,
                   regmatch_t *pmatch, char *file_name, int line_num,
                   int print_filenames);
void swap(regmatch_t *pmatch, int elem);

#endif /* S21_GREP_H */