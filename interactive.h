#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMANDS 5
#define MAX_WORDS 20

int execute_interactive() {

  _Bool exit_flag = 0;

  while (!exit_flag) {

    // printing the prompt
    printf("myPrompt> ");

    // take the command from user
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] =
        '\0'; // replace newline with null terminator

    // parse the command
    char *token;
    token = strtok(buffer, ";");

    char *commands[MAX_COMMANDS];
    int command_count = 0;

    // make the command array
    while (token != NULL && command_count < MAX_COMMANDS) {
      commands[command_count++] = strdup(token);
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
        exit_flag = 1;
        continue;
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

    // free memory allocated for commands
    for (int i = 0; i < command_count; i++) {
      free(commands[i]);
    }
  }

  printf("Exited the shell\n");
  return 0;
}