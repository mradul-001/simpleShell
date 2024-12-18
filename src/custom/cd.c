#include "../../headers.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int changeDir(char *path) {
  if (path == NULL) {

    // move to home directory
    char *home = getenv("HOME");
    chdir(home);

  } else if (chdir(path) == -1) {
    printf("No such directory: %s\n", path);
  }
  return 0;
}