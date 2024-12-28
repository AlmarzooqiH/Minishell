#include "minishell.h"

void print_envp(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        printf("declare -x %s\n", envp[i]);
        i++;
    }
}

int is_valid_identifier(char *arg)
{
    if (!isalpha(arg[0]) && arg[0] != '_')
        return (0);
    int i = 1;
    while (arg[i] && arg[i] != '=')
    {
        if (!isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void update_envp(char *arg, t_minishell_state *state)
{
    int j = 0;
    while (state->envp[j])
    {
        if (ft_strncmp(arg, state->envp[j], ft_strlen(arg)) == 0)
        {
            free(state->envp[j]);
            state->envp[j] = ft_strdup(arg);
            return;
        }
        j++;
    }
    state->envp[j] = ft_strdup(arg);
    state->envp[j + 1] = NULL;
}

void builtin_export(char **args, t_minishell_state *state)
{
    if (!args[1])
    {
        print_envp(state->envp);
        return;
    }
    int i = 1;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            printf("export: `%s': not a valid identifier\n", args[i]);
            state->exit_status = 1;
        }
        else
            update_envp(args[i], state);
        i++;
    }
    state->exit_status = 0;
}
