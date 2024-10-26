/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2024/10/26 16:30:27 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "commands.h"
# include "error.h"
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

void	process_input(const char *command);
void	process_commands(char ***commands, size_t len);
void	process_commands_wp(char ***commands, size_t len);
void	process_echo(char **commands, size_t len);
int		has_flag(char *flag, char *flag_in);
int		has_pipe(char *commands);
int		ft_execute(char *pvar, char **commands);
void	print_stdout(int fd);
char	**create_argv(int fd);
long	count_lines(int fd);
void	get_tokens(char *command, char ***tokens, char split);
void	free_tokens(char ***tokens, int n_tokens);
void	execute_binary(char ***commands, size_t size);
void	one_command(char **bdir, char **commands, int (*fd)[2], size_t cpipe);
void	process_parent(char **bdir, char **commands, int (*fd)[2],
			size_t cpipe);
void	close_pipes(int (*fd)[2], size_t npipes);
void	close_pipe(int *fd, int which);
char	**trim_command(char **commands);
int		dup_pipes(int (*fd)[2], size_t cpipe, int to);
int		init_pipes(int (**fd)[2], size_t size);
int		is_redirection(char **command, size_t split_size);
void	redierct_to_file(char **bdir, char **commands, int troa, char *dlmtr);
void	redierct_to_input(char **bdir, char **commands);
void	heredoc_to_input(char **bdir, char **commands);
void	normal_process(char **bdir, char **commands, char *fname,
			char *delimeter);
#endif