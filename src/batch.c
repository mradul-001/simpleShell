#include "../headers.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMANDS 5
#define MAX_WORDS 30

int execute_batch(char *fileName) {

  // opening the batch file
  FILE *fptr = fopen(fileName, "r");

  // storing array
  char contentOfBatchFile[255];

  int RUN = 1;

  // repeatedly reading the batchfile and executing the commands
  while (fgets(contentOfBatchFile, sizeof(contentOfBatchFile), fptr) && RUN == 1) {

    // replace newline character at the end of the line with \0
    contentOfBatchFile[strcspn(contentOfBatchFile, "\n")] = '\0';

    // get the commands out of the line
    char *commands[MAX_COMMANDS];
    int command_count = 0;

    char *token = strtok(contentOfBatchFile, ";");
    while (token != NULL && command_count < MAX_COMMANDS) {
      commands[command_count++] = token;
      token = strtok(NULL, ";");
    }

    // looping through each command
    for (int i = 0; i < command_count; i++) {

      // creating argument array
      char *args[MAX_WORDS];
      int word_count = 0;

      char *token_inner;
      token_inner = strtok(commands[i], " ");

      while (token_inner != NULL && word_count < MAX_WORDS) {
        args[word_count++] = strdup(token_inner);
        token_inner = strtok(NULL, " ");
      }

      args[word_count] = NULL; // NULL-terminate the args array

      if (args[0] == NULL)
        continue;

      if (strcmp(args[0], "exit") == 0) {
        RUN = 0;
        break;
      }

      // create a child process using fork() syscall
      pid_t pid = fork();

      if (pid == 0) {
        if (execvp(args[0], args) == -1) {
          perror("Something went wrong!");
          exit(1);
        }
      } else if (pid > 0) {
        wait(NULL);
      } else {
        perror("Fork Failed!");
      }
    }
  }

  printf("Exiting the shell");

  // closing the file
  fclose(fptr);

  return 0;
}