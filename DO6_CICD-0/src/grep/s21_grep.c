#include "./s21_grep.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  struct flags flags = {0};
  if (argc > 1) {
    int e_pattern_count = 0;
    int f_pattern_count = 0;
    char f_patterns_arr[MAX_COUNT][MAX_PATT_LEN] = {0};

    char e_patterns_arr[MAX_COUNT][MAX_PATT_LEN] = {0};
    if (check_flags(&flags, argc, argv, &e_pattern_count, &f_pattern_count,
                    e_patterns_arr, f_patterns_arr)) {
      int pattern_index = 1;
      char *pattern = get_pattern(flags, argc, argv, &pattern_index);
      if (pattern[0] != '\0') {
        strcpy(e_patterns_arr[0], pattern);
        e_pattern_count = 1;
      }
      if (flags.o) {
        flag_o_printer(flags, argc, argv, e_pattern_count, e_patterns_arr,
                       f_pattern_count, f_patterns_arr);
      } else {
        main_printer(flags, argc, argv, e_pattern_count, e_patterns_arr,
                     f_pattern_count, f_patterns_arr);
      }
    }
  } else {
    fprintf(stderr, "Usage: ./s21_grep [OPTION]... PATTERNS [FILE]...\n");
  }
  return 0;
}

char *get_pattern(struct flags flags, int argc, char **argv,
                  int *pattern_index) {
  char *pattern;
  if (flags.e == 0 && flags.f == 0) {
    while (*pattern_index < argc) {
      if ((argv[*pattern_index][0]) != '-') {
        break;
      }
      *pattern_index = *pattern_index + 1;
    }
    pattern = argv[*pattern_index];
    argv[*pattern_index] = "-e";
  } else {
    pattern = "\0";
  }
  return pattern;
}

int check_flags(struct flags *flags, int argc, char **argv,
                int *e_pattern_count, int *f_pattern_count,
                char e_patterns_arr[][MAX_PATT_LEN],
                char f_patterns_arr[][MAX_PATT_LEN]) {
  char flag;
  int check_result = 1;
  fill_patterns_arrs(argc, argv, e_pattern_count, f_pattern_count,
                     e_patterns_arr, f_patterns_arr);

  while ((flag = getopt(argc, argv, "e::ivclnhsf::o")) != -1) {
    if (flag == '?') {
      check_result = 0;
      break;
    }
    switch (flag) {
      case 'e': {
        flags->e = 1;
        break;
      }
      case 'i': {
        flags->i = 1;
        break;
      }
      case 'v': {
        flags->v = 1;
        break;
      }
      case 'c': {
        if (flags->l == 0) {
          flags->c = 1;
          flags->o = 0;
          flags->n = 0;
        } else {
          flags->c = 0;
        }
        break;
      }
      case 'l': {
        flags->l = 1;
        flags->h = 0;
        flags->o = 0;
        flags->c = 0;
        flags->n = 0;
        break;
      }
      case 'n': {
        flags->n = flags->c == 0 && flags->l == 0 ? 1 : 0;
        break;
      }
      case 'h': {
        flags->h = flags->l == 0 ? 1 : 0;
        break;
      }
      case 's': {
        flags->s = 1;
        break;
      }
      case 'f': {
        flags->f = 1;
        break;
      }
      case 'o': {
        flags->o = flags->c == 0 && flags->l == 0 ? 1 : 0;
        break;
      }
    }
  }
  return check_result;
}

void fill_patterns_arrs(int argc, char **argv, int *e_pattern_count,
                        int *f_pattern_count,
                        char e_patterns_arr[][MAX_PATT_LEN],
                        char f_patterns_arr[][MAX_PATT_LEN]) {
  int arg_num = 0;
  while (arg_num < argc && *e_pattern_count < MAX_COUNT &&
         *f_pattern_count < MAX_COUNT) {
    int i = 1;
    if (argv[arg_num][0] == '-') {
      while (argv[arg_num][i] != 'e' && argv[arg_num][i] != 'f' &&
             argv[arg_num][i] != '\0') {
        i++;
      }
      if (argv[arg_num][i] == 'e') {
        arg_num =
            add_pattern(arg_num, argv, e_pattern_count, i + 1, e_patterns_arr);
      }
      if (argv[arg_num][i] == 'f') {
        arg_num =
            add_pattern(arg_num, argv, f_pattern_count, i + 1, f_patterns_arr);
      }
    }
    arg_num++;
  }
}

int add_pattern(int arg_num, char **argv, int *pattern_num,
                int patt_first_symbol_index,
                char patterns_arr[][MAX_PATT_LEN]) {
  if (argv[arg_num][patt_first_symbol_index] == '\0') {
    arg_num++;
    strcpy(patterns_arr[*pattern_num], argv[arg_num]);
    argv[arg_num] = "-e";
  } else {
    strcpy(patterns_arr[*pattern_num], &argv[arg_num][patt_first_symbol_index]);
  }
  *pattern_num = *pattern_num + 1;
  return arg_num;
}

int main_printer(struct flags flags, int argc, char **argv, int e_pattern_count,
                 char e_patterns_arr[][MAX_PATT_LEN], int f_pattern_count,
                 char f_patterns_arr[][MAX_PATT_LEN]) {
  int file_index = get_file_index(argc, argv);
  int f_files_exist = check_f_files(f_pattern_count, f_patterns_arr);
  FILE *file;
  int regflag = flags.i == 1 ? REG_ICASE | REG_NEWLINE : REG_NEWLINE;
  int print_filenames = (file_index < argc - 1) && flags.h == 0 ? 1 : 0;
  char *file_string = (char *)calloc(MAX_PATT_LEN, 1);
  char *pattern_file_string = (char *)calloc(MAX_PATT_LEN, 1);
  char last_printed_str[MAX_PATT_LEN] = {0};
  int err = 0;

  if (file_string != NULL && pattern_file_string != NULL) {
    last_printed_str[0] = '\n';
    while (file_index < argc && f_files_exist && !err) {
      int line_num = 0;
      if ((file = fopen(argv[file_index], "r")) != NULL && !err) {
        int c_counter = 0;
        int keep_opened_file = 1;
        while (fgets(file_string, MAX_PATT_LEN - 1, file) != NULL &&
               keep_opened_file) {
          int continue_search = 1;
          line_num++;
          regex_t regex;
          int found = REG_NOMATCH;
          if (e_pattern_count > 0) {
            int i = 0;
            while (found == REG_NOMATCH && i < e_pattern_count && !err) {
              if (regcomp(&regex, e_patterns_arr[i], regflag) == 0) {
                found = regexec(&regex, file_string, 0, NULL, 0);
                regfree(&regex);
              } else {
                fprintf(stderr, "s21_grep: regcomp fail\n");
                err = 1;
              }
              i++;
            }
            if (((flags.v == 0 && found == 0) ||
                 (flags.v == 1 && found == REG_NOMATCH &&
                  f_pattern_count == 0)) &&
                !err) {
              if (flags.l == 1) {
                printf("%s\n", argv[file_index]);
                keep_opened_file = 0;
              } else {
                if (flags.c) {
                  c_counter++;
                } else {
                  if (print_filenames) {
                    printf("%s:", argv[file_index]);
                  }
                  if (flags.n == 1) {
                    printf("%d:", line_num);
                  }
                  printf("%s", file_string);
                  strcpy(last_printed_str, file_string);
                }
                continue;
              }
            }
          }
          if (f_pattern_count > 0 && keep_opened_file && !err) {
            int j = 0;
            FILE *pattern_file;
            while (j < f_pattern_count && continue_search && !err) {
              if ((pattern_file = fopen(f_patterns_arr[j], "r")) != NULL) {
                while (!err && found == REG_NOMATCH &&
                       fgets(pattern_file_string, MAX_PATT_LEN - 1,
                             pattern_file) != NULL) {
                  delete_nextline(pattern_file_string);
                  if (regcomp(&regex, pattern_file_string, regflag) == 0) {
                    found = regexec(&regex, file_string, 0, NULL, 0);
                    regfree(&regex);
                  } else {
                    fprintf(stderr, "s21_grep: regcomp fail\n");
                    err = 1;
                  }
                }
                if (found == flags.v && !err) {
                  if (flags.l) {
                    printf("%s\n", argv[file_index]);
                    keep_opened_file = 0;
                  } else {
                    if (flags.c) {
                      c_counter++;
                    } else {
                      if (print_filenames) {
                        printf("%s:", argv[file_index]);
                      }
                      if (flags.n == 1) {
                        printf("%d:", line_num);
                      }
                      printf("%s", file_string);
                      strcpy(last_printed_str, file_string);
                    }
                  }
                  continue_search = 0;
                }
                fclose(pattern_file);
              } else {
                if (flags.s == 0) {
                  fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                          f_patterns_arr[j]);
                }
              }
              j++;
            }
          }
        }
        fclose(file);
        if (flags.c && !err) {
          if (print_filenames) {
            printf("%s:", argv[file_index]);
          }
          printf("%d\n", c_counter);
        }
        if (flags.l == 0 && !err) {
          check_last_symbol(last_printed_str);
        }
      } else {
        if (flags.s == 0) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  argv[file_index]);
        }
      }
      file_index++;
    }
    free(file_string);
    free(pattern_file_string);
  } else {
    fprintf(stderr, "s21_grep: out of memory\n");
  }
  return 1;
}

int get_file_index(int argc, char **argv) {
  int index = 1;
  while (index < argc) {
    if (argv[index][0] != '-') {
      break;
    }
    index++;
  }
  return index;
}

int check_f_files(int f_pattern_count, char f_patterns_arr[][MAX_PATT_LEN]) {
  int f_files_exist = 1;
  FILE *file_checker;
  int num = 0;
  while (num < f_pattern_count &&
         (file_checker = fopen(f_patterns_arr[num], "r")) != NULL) {
    fclose(file_checker);
    num++;
  }
  if (num < f_pattern_count) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n",
            f_patterns_arr[num]);
    f_files_exist = 0;
  }
  return f_files_exist;
}

void delete_nextline(char *pattern_file_string) {
  int i = 1;
  while (pattern_file_string[i] != '\0') {
    if (pattern_file_string[i] == '\n') {
      pattern_file_string[i] = '\0';
    }
    i++;
  }
}

void check_last_symbol(char *file_string) {
  if (file_string[0] != '\0') {
    int i = 0;
    while (file_string[i] != '\n' && file_string[i] != '\0') {
      i++;
    }
    if (file_string[i] == '\0') {
      printf("\n");
    }
  }
}

int flag_o_printer(struct flags flags, int argc, char **argv,
                   int e_pattern_count, char e_patterns_arr[][MAX_PATT_LEN],
                   int f_pattern_count, char f_patterns_arr[][MAX_PATT_LEN]) {
  int file_index = get_file_index(argc, argv);
  int f_files_exist = check_f_files(f_pattern_count, f_patterns_arr);
  int print_filenames = (file_index < argc - 1) && flags.h == 0 ? 1 : 0;
  int regflag = flags.i == 1 ? REG_ICASE | REG_NEWLINE : REG_NEWLINE;
  char *file_string = (char *)calloc(MAX_PATT_LEN, 1);
  char *temp_string;
  int found = REG_NOMATCH;
  int err = 0;
  FILE *file;
  size_t nmatch = MAX_PATT_LEN;
  regex_t regex;
  regmatch_t pmatch[MAX_PATT_LEN];

  if (file_string != NULL) {
    while (file_index < argc && f_files_exist && !flags.v && !err) {
      int line_num = 0;
      if ((file = fopen(argv[file_index], "r")) != NULL) {
        while (fgets(file_string, MAX_PATT_LEN - 1, file) != NULL && !err) {
          line_num++;
          int i = 0;
          size_t pmatch_elems = 0;
          temp_string = file_string;
          int is_new_arg = 1;
          while (i < e_pattern_count && pmatch_elems < nmatch && !err) {
            if (regcomp(&regex, e_patterns_arr[i], regflag) == 0) {
              found = regexec(&regex, temp_string, nmatch,
                              pmatch + pmatch_elems, 0);
              regfree(&regex);
              if (found == 0) {
                temp_string = change_indexes(temp_string, pmatch_elems, pmatch,
                                             is_new_arg);
                is_new_arg = 0;
                pmatch_elems++;
              } else {
                temp_string = file_string;
                is_new_arg = 1;
                i++;
              }
              found = REG_NOMATCH;
            } else {
              err = 1;
              fprintf(stderr, "s21_grep: regcomp fail\n");
            }
          }
          if (f_pattern_count > 0 && !err) {
            int j = 0;
            char pattern_file_string[MAX_PATT_LEN] = {0};
            FILE *pattern_file;
            while (j < f_pattern_count && !err) {
              if ((pattern_file = fopen(f_patterns_arr[j], "r")) != NULL) {
                while (fgets(pattern_file_string, MAX_PATT_LEN - 1,
                             pattern_file) != NULL &&
                       !err) {
                  if (pattern_file_string[0] == '\n') {
                    continue;
                  }
                  delete_nextline(pattern_file_string);
                  int continue_search = 1;
                  while (continue_search && !err) {
                    if (regcomp(&regex, pattern_file_string, regflag) == 0) {
                      found = regexec(&regex, temp_string, nmatch,
                                      pmatch + pmatch_elems, 0);
                      regfree(&regex);
                      if (found == 0) {
                        temp_string = change_indexes(temp_string, pmatch_elems,
                                                     pmatch, is_new_arg);
                        is_new_arg = 0;
                        pmatch_elems++;
                      } else {
                        temp_string = file_string;
                        is_new_arg = 1;
                        continue_search = 0;
                      }
                      found = REG_NOMATCH;
                    } else {
                      err = 1;
                      fprintf(stderr, "s21_grep: regcomp fail\n");
                    }
                  }
                }
                fclose(pattern_file);
              } else {
                if (flags.s == 0) {
                  fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                          f_patterns_arr[j]);
                }
              }
              j++;
            }
          }
          if (!err) {
            sort_pmatch(pmatch_elems, pmatch);
            print_matches(flags, temp_string, pmatch_elems, pmatch,
                          argv[file_index], line_num, print_filenames);
          }
        }
        fclose(file);
      } else {
        if (flags.s == 0) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  argv[file_index]);
        }
      }
      file_index++;
    }
    free(file_string);
  } else {
    fprintf(stderr, "s21_grep: out of memory\n");
  }
  return 1;
}

char *change_indexes(char *temp_string, size_t pmatch_elems, regmatch_t *pmatch,
                     int is_new_arg) {
  temp_string = temp_string + (pmatch + pmatch_elems)->rm_eo;
  if (pmatch_elems > 0 && !is_new_arg) {
    (pmatch + pmatch_elems)->rm_so =
        (pmatch + pmatch_elems)->rm_so + (pmatch + pmatch_elems - 1)->rm_eo;
    (pmatch + pmatch_elems)->rm_eo =
        (pmatch + pmatch_elems)->rm_eo + (pmatch + pmatch_elems - 1)->rm_eo;
  }
  return temp_string;
}

void sort_pmatch(size_t pmatch_elems, regmatch_t *pmatch) {
  for (int i = pmatch_elems - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (pmatch[j].rm_so > pmatch[j + 1].rm_so) {
        swap(pmatch, j);
      } else {
        if (pmatch[j].rm_so == pmatch[j + 1].rm_so) {
          if (pmatch[j].rm_eo < pmatch[j + 1].rm_so) {
            swap(pmatch, j);
          }
        }
      }
    }
  }
}

void swap(regmatch_t *pmatch, int elem) {
  regmatch_t buffer;
  buffer.rm_so = pmatch[elem].rm_so;
  buffer.rm_eo = pmatch[elem].rm_eo;
  pmatch[elem].rm_so = pmatch[elem + 1].rm_so;
  pmatch[elem].rm_eo = pmatch[elem + 1].rm_eo;
  pmatch[elem + 1].rm_so = buffer.rm_so;
  pmatch[elem + 1].rm_eo = buffer.rm_eo;
}

void print_matches(struct flags flags, char *temp_string, size_t pmatch_elems,
                   regmatch_t *pmatch, char *file_name, int line_num,
                   int print_filenames) {
  size_t f = 0;
  regmatch_t prev_pmatch = {0};
  while (f < pmatch_elems) {
    if (!f || pmatch[f].rm_so >= prev_pmatch.rm_eo) {
      int k = pmatch[f].rm_so;
      if (print_filenames) {
        printf("%s:", file_name);
      }
      if (flags.n) {
        printf("%d:", line_num);
      }
      while (k < pmatch[f].rm_eo) {
        printf("%c", temp_string[k]);
        k++;
      }
      printf("\n");
      prev_pmatch.rm_so = pmatch[f].rm_so;
      prev_pmatch.rm_eo = pmatch[f].rm_eo;
    }
    f++;
  }
}
