// I need to implement signal handling for my Minishell project in C. The signals to handle are SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\). When either of these signals is received, the default behavior should be suppressed, and the shell should simply print a new prompt instead of terminating. 

// The signal handler should work as follows:
// - SIGINT: When the user presses Ctrl+C, the shell should print a new prompt on the same line, clearing the previous one.
// - SIGQUIT: When the user presses Ctrl+\, the shell should also print a new prompt, clearing the previous one, without terminating the program.

// I want to use the standard signal library and want to avoid process termination on these signals.

// Please provide the implementation using the `signal()` function to set up custom handlers for SIGINT and SIGQUIT. The main shell loop should keep running even after these signals are triggered.
#include "minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
    write(1, "\nminishell> ", 12);
}

void sigquit_handler(int signum)
{
    (void)signum;
    write(1, "\nminishell> ", 12);
}

int main()
{
    char *line = NULL;
    size_t len = 0;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    while (1)
    {
        write(1, "minishell> ", 11);
        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            exit(0);
        }
        printf("You entered: %s", line);
    }
    return 0;
}