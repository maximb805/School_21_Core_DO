#ifndef S21_CAT_H
#define S21_CAT_H

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

int get_first_filename_index(int argc, char **argv);
int check_flags(struct flags *flags, int argc, char **argv);
int print_files(struct flags flags, int argc, int first_file_index,
                char **argv);

#endif /* S21_CAT_H */