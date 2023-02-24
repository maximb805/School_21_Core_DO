#include "./s21_cat.h"

#include <getopt.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    struct flags flags = {0};
    int check_result = check_flags(&flags, argc, argv);
    if (check_result) {
      int first_file_index = get_first_filename_index(argc, argv);
      print_files(flags, argc, first_file_index, argv);
    }
  }
  return 0;
}

int get_first_filename_index(int argc, char **argv) {
  int first_file_index = 1;
  while (first_file_index < argc) {
    if ((argv[first_file_index][0]) != '-') {
      break;
    }

    first_file_index++;
  }

  return first_file_index;
}

int check_flags(struct flags *flags, int argc, char **argv) {
  char flag;
  int check_result = 1;
  struct option options[4] = {0};

  options[0].name = "number-nonblank";
  options[0].val = 'b';

  options[1].name = "number";
  options[1].val = 'n';

  options[2].name = "squeeze-blank";
  options[2].val = 's';

  while ((flag = getopt_long(argc, argv, "benstvET", options, NULL)) != -1) {
    if (flag == '?') {
      check_result = 0;
      break;
    }
    switch (flag) {
      case 'b': {
        flags->b = 1;
        flags->n = 0;
        break;
      }
      case 'v': {
        flags->v = 1;
        break;
      }
      case 'e': {
        flags->e = 1;
        flags->v = 1;
        break;
      }
      case 'n': {
        flags->n = flags->b == 1 ? 0 : 1;
        break;
      }
      case 's': {
        flags->s = 1;
        break;
      }
      case 't': {
        flags->v = 1;
        flags->t = 1;
        break;
      }
      case 'E': {
        flags->e = 1;
        break;
      }
      case 'T': {
        flags->t = 1;
        break;
      }
    }
  }
  return check_result;
}

int print_files(struct flags flags, int argc, int file_index, char **argv) {
  FILE *file;
  char char_this = 't';
  char char_prev = 'p';
  int was_blank = 0;

  int is_new_line = 1;
  int line_num = 0;
  while (file_index < argc) {
    if ((file = fopen(argv[file_index], "r")) != NULL) {
      while ((char_this = fgetc(file)) != EOF) {
        if ((flags.n == 1 || flags.b == 1) && is_new_line == 1 &&
            !(flags.b == 1 && char_this == '\n') &&
            !(flags.s == 1 && was_blank == 1 && char_this == '\n')) {
          line_num++;
          printf("%6d\t", line_num);
          is_new_line = 0;
        }

        if (char_this == '\t' && flags.t == 1) {
          printf("^I");
          continue;
        }

        if (was_blank == 1 && char_this != '\n') {
          was_blank = 0;
        }

        if (flags.v == 1 && (char_this < 32 || char_this == 127) &&
            char_this != '\n' && char_this != '\t') {
          printf("^");
          if (char_this == 127) {
            char_this = -1;
          }
          char_this = char_this + 64;
        }

        if (!(was_blank == 1 && char_this == '\n' && flags.s == 1)) {
          if (flags.e == 1 && char_this == '\n') {
            printf("$");
          }
          printf("%c", char_this);
        }

        if (char_this == '\n' && char_prev == '\n') {
          was_blank = 1;
        }

        char_prev = char_this;
        is_new_line = char_this == '\n' ? 1 : 0;
      }
      fclose(file);
    } else {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n",
              argv[file_index]);
    }
    file_index++;
  }
  return 1;
}
