#define MAX_LINE 80 // The maximum length of a command
#define MAX_ARGS 10 // The maximum number of arguments

// A function to parse the input line into words and store them in an array
void parse_line(char *line, char **args) {
  int i = 0;
  char *token = strtok(line, " \n"); // Split the line by spaces and newline
  while (token != NULL && i < MAX_ARGS) { // Loop until the end of the line or the maximum number of arguments
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
  char *args[MAX_ARGS]; // The command line arguments
  int status; // The exit status of the child process
  int should_run = 1; // A flag to determine when to exit the program

  // Set up the signal handler for SIGINT
  signal(SIGINT, sigint_handler);

  while (should_run) { // Loop until the user enters "exit" or "quit"
    printf("myshell> "); // Display the prompt
    fflush(stdout); // Flush the output buffer
    fgets(line, MAX_LINE, stdin); // Read a line of input from the user
    parse_line(line, args); // Parse the input into words and store them in an array

    if (args[0] == NULL) { // If the user entered an empty line, do nothing
      continue;
    } else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) { // If the user entered "exit" or "quit", exit the program
      should_run = 0;
    } else { // Otherwise, execute the command
      pid_t pid = fork(); // Fork a child process
      if (pid < 0) { // If the fork failed, print an error message and exit
        perror("Fork failed");
        exit(1);
      } else if (pid == 0) { // If this is the child process, execute the command using execvp
        if (execvp(args[0], args) < 0) { // If the execvp failed, print an error message and exit
          perror("Execvp failed");
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
