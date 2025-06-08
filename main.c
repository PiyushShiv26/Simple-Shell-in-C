#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_PATH_LENGTH 1024

void echo_tokenize_and_print(const char *input) {
    int i = 0;
    int first = 1;
    int prev_was_space = 1; // Start as true to avoid leading space

    while (input[i]) {
        // Check for spaces
        if (input[i] == ' ') {
            prev_was_space = 1;
            i++;
            continue;
        }

        char token[MAX_PATH_LENGTH] = {0};
        int j = 0;

        // Handle quoted token
        if (input[i] == '\'' || input[i] == '"') {
            char quote = input[i++];
            while (input[i] && input[i] != quote) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            if (input[i] == quote) i++; // Skip closing quote
        } else {
            // Handle unquoted token
            while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"') {
                token[j++] = input[i++];
            }
            token[j] = '\0';
        }

        // Only print space if previous character was a space and not the first token
        if (!first && prev_was_space) printf(" ");
        printf("%s", token);
        first = 0;
        prev_was_space = 0;
    }
    printf("\n");
}

void cat_tokenize_and_print(const char *input) {
    int i = 0, first = 1;
    while (input[i]) {
        // Skip spaces
        while (input[i] == ' ') i++;
        if (input[i] == '\0') break;

        char token[MAX_PATH_LENGTH] = {0};
        int j = 0;

        // Handle quoted token
        if (input[i] == '\'' || input[i] == '"') {
            char quote = input[i++];
            while (input[i] && input[i] != quote) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            if (input[i] == quote) i++; // Skip closing quote
        } else {
            // Handle unquoted token
            while (input[i] && input[i] != ' ') {
                token[j++] = input[i++];
            }
            token[j] = '\0';
        }

        // Print file contents
        FILE *fp = fopen(token, "r");
        if (fp) {
            int c;
            while ((c = fgetc(fp)) != EOF) {
                putchar(c);
            }
            fclose(fp);
        } else {
            printf("cat: %s: No such file or directory\n", token);
        }
        first = 0;
    }
    fflush(stdout);
}

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(1){
  printf("$ ");
  fflush(stdout);

  // Wait for user input
  char input[MAX_PATH_LENGTH];
  fgets(input, sizeof(input), stdin);
  input[strlen(input) - 1] = '\0';

  // exit command
  if (strcmp(input, "exit 0") == 0) break;
  
  // cd command
  if (strncmp(input, "cd ", 3) == 0) {
    char *path = input + 3;
    if (strcmp(path, "~") == 0) {
        path = getenv("HOME");
    } 
    if (chdir(path) != 0) {
        printf("cd: %s: No such file or directory\n", path);
    }
    continue;
  }

  // pwd command
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
    char *message = input + 5;
    echo_tokenize_and_print(message);
    continue;
  }

  // cat command
  if (strncmp(input, "cat ", 4) == 0) {
    char *file = input + 4;
    cat_tokenize_and_print(file);
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
