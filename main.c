#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_WORDS 30

int main(){
    
    while (1) {
        
        

        // printing the  prompt
        printf("myPrompt> ");
    

        // take the command from user
        char buffer[50];
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // replacing newline with null terminator

        

        // parse the command
        char *token;
        token = strtok(buffer, " ");

        


        // creating argument array
        char *args[MAX_WORDS];
        int word_count = 0;

        // ensuring that command still have words and it don't have too many words
        while (token != NULL && word_count < MAX_WORDS) {
            args[word_count++] = strdup(token);
            token = strtok(NULL, " ");
        }
        // NULL terminating the args array
        args[word_count] = NULL;



        if (args[0] == "NULL") continue;
        if (args[0] == "exit") break;



        // creating a child process using fork() syscall
        pid_t pid = fork();

        if (pid == 0) {
            if(execvp(args[0], args) == -1){
                perror("Something went wrong!");
                exit(1);
            } else if (pid > 1) {
                wait(NULL); 
            } else {
                perror("Fork Failed!");
            }
        }
        

    }

    return 0;
}
