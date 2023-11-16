int main(void) {
char *line;
size_t len = 0;
while (1) {
printf("#shimple_shell$ ");
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

    
        line[strcspn(line, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execlp(line, line, (char *)NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }
    }

    free(line);
    return 0;
}
