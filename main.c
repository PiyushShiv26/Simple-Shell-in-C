#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_PATH_LENGTH 1024

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(1){
  printf("$ ");

  // Wait for user input
  char input[MAX_PATH_LENGTH];
  fgets(input, sizeof(input), stdin);
  input[strlen(input) - 1] = '\0';

  // exit command
  if (strcmp(input, "exit 0") == 0) break;

  if (strcmp(input, "pwd") == 0) {
    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd); 
    } else {
        perror("getcwd"); 
    }
    continue;
  }

  //echo command
  if (strncmp(input, "echo ", 5) == 0) {
    printf("%s\n", input + 5);
    continue;
  }

  // custom_exe command
  if (strncmp(input, "custom_exe_", 11) == 0) {
    char *args[3]; 
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL && i < 2) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("exec failed"); 
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
    continue;
  }

  //type command
  if (strncmp(input, "type ", 5) == 0) {
    char *command = input + 5;
    char *path = strdup(getenv("PATH"));
    int found = 0; 

    if (strcmp(command, "echo") == 0 || strcmp(command, "exit") == 0 || strcmp(command, "type") == 0 || strcmp(command, "pwd") == 0){
        printf("%s is a shell builtin\n", command);
        found = 1; 
    } 
    else if (path != NULL) {
      char *dir = strtok(path, ":");
      while (dir != NULL) {
          char full_path[MAX_PATH_LENGTH];
          snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

          // Check if the file exists and is executable
          if (access(full_path, X_OK) == 0) {
              printf("%s is %s\n", command, full_path);
              found = 1; 
              break;
          }
          dir = strtok(NULL, ":");
      }
      free(path);
    }
    if (!found) {
        printf("%s: not found\n", command);
    }
    continue;
    }
    printf("%s: command not found\n", input);
  }
  return 0;
}
