#define MAX_LINE 80 // The maximum length of a command

// A function to handle the SIGINT signal (Ctrl-C)
void sigint_handler(int sig) {
  printf("\nYou pressed Ctrl-C. To exit the shell, type \"exit\" or \"quit\".\n");
}

int main(void) {
  char line[MAX_LINE]; // The input line
  char *args[2]; // The command line arguments
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
      args[0] = line; // Store the command in the first argument
      args[1] = NULL; // Terminate the argument array with a null pointer
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
