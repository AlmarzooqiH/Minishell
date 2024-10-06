/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2024/10/06 22:19:05 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
             /'\_/`\  __          __         /\ \            /\_ \  /\_ \     
            /\      \/\_\    ___ /\_\    ____\ \ \___      __\//\ \ \//\ \    
            \ \ \__\ \/\ \ /' _ `\/\ \  /',__\\ \  _ `\  /'__`\\ \ \  \ \ \   
             \ \ \_/\ \ \ \/\ \/\ \ \ \/\__, `\\ \ \ \ \/\  __/ \_\ \_ \_\ \_ 
              \ \_\\ \_\ \_\ \_\ \_\ \_\/\____/ \ \_\ \_\ \____\/\____\/\____\
               \/_/ \/_/\/_/\/_/\/_/\/_/\/___/   \/_/\/_/\/____/\/____/\/____/
*/

#ifndef MINISHELL_H
# define MINISHELL_H
/*
                /\__  _\                /\_ \              /\ \                  
                \/_/\ \/     ___     ___\//\ \    __  __   \_\ \     __    ____  
                   \ \ \   /' _ `\  /'___\\ \ \  /\ \/\ \  /'_` \  /'__`\ /',__\ 
                    \_\ \__/\ \/\ \/\ \__/ \_\ \_\ \ \_\ \/\ \L\ \/\  __//\__, `\
                    /\_____\ \_\ \_\ \____\/\____\\ \____/\ \___,_\ \____\/\____/
                    \/_____/\/_/\/_/\/____/\/____/ \/___/  \/__,_ /\/____/\/___/
*/
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include "error.h"
# include "commands.h"
# include "../libft/libft.h"
/*
 ____    __  __  __  __  ____    ______  ______   _____   __  __     
/\  _`\ /\ \/\ \/\ \/\ \/\  _`\ /\__  _\/\__  _\ /\  __`\/\ \/\ \    
\ \ \L\_\ \ \ \ \ \ `\\ \ \ \/\_\/_/\ \/\/_/\ \/ \ \ \/\ \ \ `\\ \   
 \ \  _\/\ \ \ \ \ \ , ` \ \ \/_/_ \ \ \   \ \ \  \ \ \ \ \ \ , ` \  
  \ \ \/  \ \ \_\ \ \ \`\ \ \ \L\ \ \ \ \   \_\ \__\ \ \_\ \ \ \`\ \ 
   \ \_\   \ \_____\ \_\ \_\ \____/  \ \_\  /\_____\\ \_____\ \_\ \_\
    \/_/    \/_____/\/_/\/_/\/___/    \/_/  \/_____/ \/_____/\/_/\/_/
                                                                     
                                                                     
 ____    ____    _____   ______  _____   ______  __    __  ____    ____      
/\  _`\ /\  _`\ /\  __`\/\__  _\/\  __`\/\__  _\/\ \  /\ \/\  _`\ /\  _`\    
\ \ \L\ \ \ \L\ \ \ \/\ \/_/\ \/\ \ \/\ \/_/\ \/\ `\`\\/'/\ \ \L\ \ \ \L\_\  
 \ \ ,__/\ \ ,  /\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ `\ `\ /'  \ \ ,__/\ \  _\L  
  \ \ \/  \ \ \\ \\ \ \_\ \ \ \ \ \ \ \_\ \ \ \ \  `\ \ \   \ \ \/  \ \ \L\ \
   \ \_\   \ \_\ \_\ \_____\ \ \_\ \ \_____\ \ \_\   \ \_\   \ \_\   \ \____/
    \/_/    \/_/\/ /\/_____/  \/_/  \/_____/  \/_/    \/_/    \/_/    \/___/ 

*/
void	process_input(const char *command);
void	process_commands(char **commands, size_t len);
void	process_commands_wp(char ***commands, size_t len);
void	process_echo(char **commands, size_t len);
int		has_flag(char *flag, char *flag_in);
int		has_pipe(char *commands);
void	ft_execute(char	*pvar, char **commands, char **av);
void	execute_binary(char	**commands, char **av);
void	print_stdout(void);
char	**create_argv(void);
long	count_lines(void);
void	get_tokens(char *command, char ***tokens, char split);
void	free_tokens(char ***tokens, int n_tokens);
#endif