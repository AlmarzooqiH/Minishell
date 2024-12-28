#include "minishell.h"

// Function to handle 'cd' with no arguments (go to the home directory)
void cd_home(t_minishell_state *state)
{
    // Get the home directory from the environment variable
    char *home = getenv("HOME");
    if (home)
    {
        // Attempt to change to the home directory
        if (chdir(home) != 0)
        {
            perror("cd");  // Print an error if chdir() fails
            state->exit_status = 1;  // Set the exit status to 1 if failed
        }
        else
            state->exit_status = 0;  // Set the exit status to 0 if successful
    }
    else
    {
        // If HOME is not set, print an error message
        fprintf(stderr, "cd: HOME not set\n");
        state->exit_status = 1;
    }
}

// Function to handle 'cd -' (change to the previous directory)
void cd_previous(t_minishell_state *state)
{
    // If a previous directory is stored in the state, change to it
    if (state->previous_dir)
    {
        if (chdir(state->previous_dir) != 0)
        {
            perror("cd");  // Print an error if chdir() fails
            state->exit_status = 1;  // Set the exit status to 1 if failed
        }
        else
        {
            // Optionally, print the previous directory after changing
            printf("%s\n", state->previous_dir);
            state->exit_status = 0;  // Set the exit status to 0 if successful
        }
    }
    else
    {
        // If no previous directory is stored, print an error message
        fprintf(stderr, "cd: No previous directory\n");
        state->exit_status = 1;
    }
}

// Function to handle 'cd <directory>' (change to the specified directory)
void cd_change_directory(char *dir, t_minishell_state *state)
{
    // Attempt to change to the directory specified by the user
    if (chdir(dir) != 0)
    {
        perror("cd");  // Print an error if chdir() fails
        state->exit_status = 1;  // Set the exit status to 1 if failed
    }
    else
    {
        state->exit_status = 0;  // Set the exit status to 0 if successful
    }
}

// Main function for the 'cd' builtin command
void builtin_cd(char **args, t_minishell_state *state)
{
    // Case 1: If no arguments are provided, change to the home directory
    if (!args[1])
    {
        cd_home(state);
    }
    // Case 2: If the argument is "-", change to the previous directory
    else if (strcmp(args[1], "-") == 0)
    {
        cd_previous(state);
    }
    // Case 3: Change to the specified directory
    else
    {
        char current_dir[1024];
        if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        {
            if (state->previous_dir)
                free(state->previous_dir);
            state->previous_dir = strdup(current_dir);
        }
        // Change to the directory specified by the user
        cd_change_directory(args[1], state);
    }
}
