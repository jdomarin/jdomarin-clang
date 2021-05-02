#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
  DIR *dirp;
  struct dirent *dp;

  dirp = opendir(".");
  while ((dp = readdir(dirp))!=NULL) {
    printf("%s\t%d\n", dp->d_name, dp->d_ino);
  }
  closedir(dirp);
}
