#include "includes/minishell.h"

// Function to handle 'cd' with no arguments (go to the home directory)
void cd_home(t_commands *cmds)
{
    char *home;

    (void)cmds;
	home = getenv("HOME");
    if (home)
    {
        if (chdir(home) != 0)
		return (perror("cd"));
    }
    else
		return (perror("cd: HOME not set\n"));
}

// Function to handle 'cd -' (change to the previous directory)
void cd_previous(t_commands *cmds)
{
    // If a previous directory is stored in the state, change to it
    if (cmds->previous_dir)
    {
        if (chdir(cmds->previous_dir) != 0)
        {
            perror("cd");  // Print an error if chdir() fails
        }
        else
        {
            // Optionally, print the previous directory after changing
            printf("%s\n", cmds->previous_dir);
        }
    }
    else
    {
        // If no previous directory is stored, print an error message
        fprintf(stderr, "cd: No previous directory\n");
    }
}

// Function to handle 'cd <directory>' (change to the specified directory)
void cd_change_directory(t_commands *cmds)
{
    // Attempt to change to the directory specified by the user
    if (chdir(cmds->cmds[cmds->cc][1]) != 0)
        perror("cd");  // Print an error if chdir() fails
}

// Main function for the 'cd' builtin command
void builtin_cd(t_commands *cmds)
{
	char *current_dir;

    if (strcmp(cmds->cmds[cmds->cc][1], "-") == 0)
{        cd_home(cmds);
}
	current_dir = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!current_dir)
		return (perror("current_dir"));
    if (getcwd(current_dir, BUFFER_SIZE) != NULL)
    {
        if (cmds->previous_dir)
            free(cmds->previous_dir);
        cmds->previous_dir = strdup(current_dir);
    }
    cd_change_directory(cmds);
}

