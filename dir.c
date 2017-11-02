#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


void print_size(size_t size) {
  char str[100];
  size_t gb = 0;
  size_t mb = 0;
  size_t kb = 0;
  size_t b = size;
  kb = b / 1024;
  b = b % 1024;
  mb = kb / 1024;
  kb = kb % 1024;
  gb = mb / 1024;
  mb = mb % 1024;
  sprintf(str, "%luGB %luMB %luKB %luB", gb, mb, kb, b);
  printf("Total Directory Size: %s\n", str);
}

int main() {

  char * dir_to_read = ".";

  printf("Directory statistics: %s\n", dir_to_read);

  DIR *d;
  int file_num = 0;
  struct dirent * files[100];
  int dir_num = 0;
  struct dirent * dirs[100];
  d = opendir(dir_to_read);
  int dir_size = 0;

  struct dirent *entry;
  entry = readdir(d);
  while (entry) {
    if (entry->d_type == DT_DIR) {
      dirs[dir_num] = entry;
      dir_num++;
    }
    else {
      files[file_num] = entry;
      file_num++;
    }

    struct stat sb;
    stat( entry->d_name, &sb );
    dir_size += sb.st_size;

    entry = readdir(d);
  }

  print_size(dir_size);

  int i;
  printf("Directories:\n");
  for (i = 0; i < dir_num; i++) {
    printf("%s\n", dirs[i]->d_name);
  }

  printf("Regular files:\n");
  for (i = 0; i < file_num; i++) {
    printf("%s\n", files[i]->d_name);
  }

  closedir(d);
}
