#include "simple_shell.h"

// A function to parse the input line into words and store them in an array
void parse_line(char *line, char **args) {
  int i = 0;
  char *token = strtok(line, " \n"); // Split the line by spaces and newline
  while (token != NULL && i < MAX_LINE) { // Loop until the end of the line or the maximum number of words
    args[i] = token; // Store the token in the array
    i++;
    token = strtok(NULL, " \n"); // Get the next token
  }
  args[i] = NULL; // Terminate the array with a null pointer
}

// A function to handle the SIGINT signal (Ctrl-C)
void sigint_handler(int sig) {
  printf("\nYou pressed Ctrl-C. To exit the shell, type \"exit\" or \"quit\".\n");
}

int main(void) {
  char line[MAX_LINE]; // The input line
  char *args[MAX_LINE]; // The command line arguments
  int status; // The exit status of the child process
  char *environ[] = {NULL}; // The environment variables

  // Set up the signal handler for SIGINT
  signal(SIGINT, sigint_handler);

  while (1) { // Loop indefinitely
    printf("$ "); // Print the prompt
    fflush(stdout); // Flush the output buffer
    if (fgets(line, MAX_LINE, stdin) == NULL) { // If the user entered EOF (Ctrl-D), exit the program
      printf("\n");
      break;
    }
    line[strcspn(line, "\n")] = '\0'; // Remove the trailing newline from the input
    if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) { // If the user entered "exit" or "quit", exit the program
      break;
    } else if (line[0] == '\0') { // If the user entered an empty line, do nothing
      continue;
    } else { // Otherwise, execute the command
      parse_line(line, args); // Parse the input into words and store them in an array
      pid_t pid = fork(); // Fork a child process
      if (pid < 0) { // If the fork failed, print an error message and exit
        perror("Fork failed");
        exit(1);
      } else if (pid == 0) { // If this is the child process, execute the command using execve
        if (execve(args[0], args, environ) < 0) { // If the execve failed, print an error message and exit
          perror("Execve failed");
          exit(1);
        }
      } else { // If this is the parent process, wait for the child to terminate and return the exit status
        waitpid(pid, &status, 0);
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
      }
    }
  }
  return 0;
}
