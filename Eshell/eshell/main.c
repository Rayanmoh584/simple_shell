#include "main.h"

#define BUFFER_SIZE 1024
int main(void) {
    char *line;
    size_t len = 0;

    while (1) {
        printf("#cisfun$ ");
        if (getline(&line, &len, stdin) == -1) {
            if (feof(stdin)) {
                printf("\n");
                free(line);
                exit(EXIT_SUCCESS);
            } else {
                perror("getline");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        // remove the newline character at the end
        line[strcspn(line, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execlp(line, line, (char *)NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // parent process 
            wait(NULL);
        }
    }

    free(line);
    return 0;
}
