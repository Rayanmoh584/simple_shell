#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 80 // The maximum length of a command

// A function to parse the input line into words and store them in an array
void parse_line(char *line, char **args);

// A function to handle the SIGINT signal (Ctrl-C)
void sigint_handler(int sig);

#endif
