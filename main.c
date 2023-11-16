#inlude "main.h"
#define MAX_LINE 80 // The maximum length of a command
int main(void) {
  char line[MAX_LINE]; // The input line
  while (1) { // Loop indefinitely
    printf("$ "); // Print the prompt
    fflush(stdout); // Flush the output buffer
    fgets(line, MAX_LINE, stdin); // Read a line of input from the user
    if (strcmp(line, "exit\n") == 0 || strcmp(line, "quit\n") == 0) { // If the user entered "exit" or "quit", exit the program
      break;
    } else { // Otherwise, print the input on the next line
      printf("%s", line);
    }
  }
  return 0;
}
