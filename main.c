#inlude "main.h"
int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int status;

    while (1) {
        printf("shell> ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL) {
            arguments[i++] = token;
            token = strtok(NULL, " ");
        }

        arguments[i] = NULL;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(arguments[0], arguments);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
