/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2025/01/20 08:04:09 by hamad            ###   ########.fr       */
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
int		gs_status(int st, int gors);
void	process_input(const char *command, char **envp);
int		validate_command(char *command);
int		ciec(char ***tokens, int i, int npipes);
int		cife(char ***token, int *i, int *j);
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
void	cps(int (*p)[2], size_t npipes);
void	cp(int *p, int which);
char	**trim_command(char **commands);
void	set_fds(int *fd, int which);
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
void	dup_heredoc(t_commands *cmds);
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
void	isbuiltin(t_commands *cmds);
char	*extract_env_name(const char *str);
char	*find_env_value(t_commands *cmds, const char *env);
int		handle_n_flag(t_commands *cmds, int *index);
void	process_echo_argument(t_commands *cmds, const char *arg);
void	print_single_quoted_content(const char *str);
void	print_double_quoted_content(t_commands *cmds, const char *str);
void	print_normal_text(t_commands *cmds, const char *str);
void	print_quote_error(const char *arg);
char	is_opening_quote(const char *str);
int		is_closing_quote(const char *str, char quote_char);
int		is_middle_of_quote(const char *str);
int		is_valid_quoted_part(char **cmd, int current_index);
// int		find_closing_quotes(char **cmd, int current_index, char quote_char);
int		find_opening_quote(char **cmd, int current_index, char *quote_char);
void	close_fd(t_commands *cmds);

int		handle_quotes(const char *str, int i);
char	*expand_env(t_commands *cmds, const char *str);
void	update_envp_helper(t_commands *cmds, char *name, char *expanded_value);
char	*get_env_value(t_commands *cmds, const char *var_name);
char	*get_var_name(const char *str, int *i);
void	expand_variable_helper(t_commands *cmds,
			const char *str, t_expand_vars *vars);

int		starts_with_quote(char *token, char *quote_char);
int		is_quote_closed_in_token(char *token, char quote_char);
int		find_closing_quote(char **tokens, int start_j, int i, char quote_char);
int		validate_quotes(char ***tokens, int i, int j);
int		process_command_segment(char ***tokens, int i, int npipes);
int		skip_whitespace(const char *command);
void	init_quote_tracking(t_quote_info *info);
int		is_quote(char c);
void	process_quote(char c, t_quote_info *info, int pos);
int		init_space_check(const char *command, int pos);
void	process_space_quote(char c, t_quote_info *info);
char	**get_command(char *temp);
void	get_end(char *command, char split, int *j);
#endif