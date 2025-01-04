#include "includes/minishell.h"

/**
 * @brief This function will search for and expand environment variables.
 * @param cmds The commands structure.
 * @param str The string containing the environment variable.
 * @return Allocated string containing the expanded value or empty string if env var doesn't exist.
 */
char *expand_env(t_commands *cmds, const char *str)
{
    char *tmp;
    char *env;
    char *value = NULL;
    
    tmp = ft_substr(str, 1, ft_strlen(str));
    if (!tmp)
        return (NULL);
        
    env = ft_strtrim(tmp, "$\"");
    free(tmp);
    if (!env)
        return (NULL);
        
    int i = 0;
    while (cmds->envp[i])
    {
        if (ft_isprefix(cmds->envp[i], env))
        {
            value = ft_strdup(ft_strchr(cmds->envp[i], '=') + 1);
            break;
        }
        i++;
    }
    free(env);
    // Return empty string if environment variable is not found
    if (!value)
        return (ft_strdup(""));
    return (value);
}

/**
 * @brief Print content between double quotes, expanding env vars
 * @param cmds Command structure
 * @param str String to process
 */
void print_double_quoted_content(t_commands *cmds, const char *str)
{
    int i = 1;  // Skip first quote
    
    while (str[i] && str[i] != '\"')
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '\"')
        {
            char *value = expand_env(cmds, str + i);
            if (value)
            {
                printf("%s", value);
                free(value);
                // Skip the variable name
                while (str[i + 1] && str[i + 1] != '\"' && str[i + 1] != '$')
                    i++;
            }
        }
        else
            printf("%c", str[i]);
        i++;
    }
}

/**
 * @brief Print content between single quotes (literal)
 * @param str String to process
 */
void print_single_quoted_content(const char *str)
{
    int i = 1;  // Skip first quote
    while (str[i] && str[i] != '\'')
    {
        printf("%c", str[i]);
        i++;
    }
}

/**
 * @brief Print normal text, handling environment variables
 * @param cmds Command structure
 * @param str String to process
 */
void print_normal_text(t_commands *cmds, const char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
        {
            char *value = expand_env(cmds, str + i);
            if (value)
            {
                printf("%s", value);
                free(value);
                while (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '$')
                    i++;
            }
        }
        else
            printf("%c", str[i]);
        i++;
    }
}

/**
 * @brief Echo command implementation
 * @param cmds Command structure
 */
void builtin_echo(t_commands *cmds)
{
    int     i;
    int     n_flag;
    char    first_char;
    
    i = 1;
    n_flag = 0;
    if (ft_strcmp(cmds->c[cmds->cc][i], NL_FLAG))
    {
        n_flag = 1;
        i++;
    }
    while (cmds->c[cmds->cc][i])
    {
        first_char = cmds->c[cmds->cc][i][0];
        if (first_char == '\'')
            print_single_quoted_content(cmds->c[cmds->cc][i]);
        else if (first_char == '\"')
            print_double_quoted_content(cmds, cmds->c[cmds->cc][i]);
        else
            print_normal_text(cmds, cmds->c[cmds->cc][i]);
        if (cmds->c[cmds->cc][i + 1])
            printf(" ");
        i++;
    }
    if (!n_flag)
        printf("\n");
}
