#include "./headers.h"
#include "./headers.h"

int main(int argc, char *argv[]) {

  if (!argv[1]) {
    execute_interactive();
  } else {
    execute_batch(argv[1]);
  }
  return 0;
}