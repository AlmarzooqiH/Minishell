/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2025/01/01 23:45:46 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "commands.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdlib.h>

//If we decide to add clear function, we just need to printf this: \033[H\033[J
void	process_input(const char *command, char **envp);
int		validate_command(char *command);
void	init(t_commands *cmds, const char *command);
void	init2(t_commands *cmds);
void	init3(t_commands *cmds);
void	set_redirectons(t_commands *cmds);
int		count_tokens(char **tokens);
void	free_cmds(t_commands *cmds);
void	free_cmds2(t_commands *cmds);
void	set_isbash(t_commands *cmds);
void	set_files(t_commands *cmds);
void	execute_binary(t_commands *cmds);
void	execute_cmd(t_commands *cmds);
void	execute_bash(t_commands *cmds);
char	**extract_command(t_commands *cmds);
int		has_flag(char *flag, char *flag_in);
int		has_pipe(char *commands);
int		ft_execute(char *pvar, char **commands);
int		ft_execute2(char **commands);
void	normal_execution(t_commands *cmds);
void	get_tokens(char *command, char ***tokens, char split);
void	free_tokens(char ***tokens, int n_tokens);
void	cpipes(int (*p)[2], size_t npipes);
void	cpipe(int *p, int which);
char	**trim_command(char **commands);
int		dup_pipes(t_commands *cmds);
int		init_pipes(int (**p)[2], int clen);
int		is_redirection(char *command);
int		count_redirections(char **command);
int		is_bashsyntax(char **command);
int		is_alone(char *s);
int		get_total_rediractions(char ***commands);
char	*gfn(char *command, int redirection);
int		has_redirection(t_commands *cmds);
void	process_redir(t_commands *cmds);
void	create_files(t_commands *cmds);
int		check_file(t_commands *cmds);
int		process_heredoc(t_commands *cmds);
void	close_files(t_commands *cmds);
void	free_variables(char **t, char **y, char **u, char **s);
int		parent_functions(t_commands *cmds);
void	child_functions(t_commands *cmds);
void	builtin_cd(t_commands *cmds);
void	cd_home(void);
void	cd_previous(t_commands *cmds);
void	cd_change_directory(t_commands *cmds);
void	builtin_exit(t_commands *cmds);
void	builtin_unset(t_commands *cmds);
void	builtin_pwd(void);
void	builtin_echo(t_commands *cmds);
void	check_if_success(t_commands *cmds);
void	builtin_env(t_commands *cmds);
void	builtin_export(t_commands *cmds);
void	init_signals(void);
void	signal_handler(int signal_num);
#endif
