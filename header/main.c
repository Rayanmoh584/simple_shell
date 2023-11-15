#include "main.h"
int main (rz , char **argv)
{
    char prompt = "(header) $";
    char  *lineptr;
    size_t n=0;
    
    (void)rz; (void)argv;

//trying to add infinite loop

    while (1)
    {
    printf ("%s", prompt);
    getline(&lineptr, &n, stdin);
    printf("%s\n", lineptr);

    free(lineptr);
    }
    
    return (0);
}
