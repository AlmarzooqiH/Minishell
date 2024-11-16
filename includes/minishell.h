/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2024/11/16 17:15:36 by hamad            ###   ########.fr       */
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
//If we decide to add clear function, we just need to printf this: \033[H\033[J
void	process_input(const char *command);
void	process_commands(char ***commands, size_t len);
void	process_commands_wp(char ***commands, size_t len);
void	process_echo(char **commands, size_t len);
int		has_flag(char *flag, char *flag_in);
int		has_pipe(char *commands);
int		ft_execute(char *pvar, char **commands);
int		ft_execute2(char **commands);
void	print_stdout(int fd);
char	**create_argv(int fd);
long	count_lines(int fd);
void	get_tokens(char *command, char ***tokens, char split);
void	free_tokens(char ***tokens, int n_tokens);
void	execute_binary(char ***commands, size_t size);
void	one_command(char **bdir, char **commands, int (*fd)[2], size_t *cpipe);
void	process_parent(char **bdir, char **commands, int (*fd)[2],
			size_t cpipe);
void	close_pipes(int (*fd)[2], size_t npipes);
void	close_pipe(int *fd, int which);
char	**trim_command(char **commands);
int		dup_pipes(int (*fd)[2], size_t cpipe, int to);
int		init_pipes(int (**fd)[2], size_t clen, size_t t_redir);
int		is_redirection(char *command);
void	redierct_to_file(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe, int troa);
void	redierct_to_input(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe);
void	heredoc_to_input(char **bdir, char **commands, char *dlmtr, int (*fd)[2], size_t *cpipe);
void	normal_process(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe);
size_t	count_redirections(char **command);
int		is_bashsyntax(char **command);
int		is_alone(char *s);
void	process_bash(char **bdir, char **command, int (*fd)[2], size_t *cpipe, size_t npipes);
void	process_redirection(char **bdir, char **command, char *fname, int re, int *cflag, int (*fd)[2], size_t *cpipe);
void	process_alone(char **bdir, char **command, size_t *i, int redirection, int *cflag, int (*fd)[2], size_t *cpipe);
void	process_not_alone(char **bdir, char **command, size_t *i, int redirection, int *cflag, int (*fd)[2], size_t *cpipe);
char	*get_filename(char *command, int redirection);
size_t	get_total_rediractions(char ***commands);
void	redierct_to_files(char *fname, int re, int (*fd)[2], size_t *cpipe);
#endif