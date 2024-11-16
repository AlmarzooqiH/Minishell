/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:25 by hamad             #+#    #+#             */
/*   Updated: 2024/11/16 17:13:13 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# define ECHO_COMMAND "echo\0"
# define CD_COMMAND "cd\0"
# define PWD_COMMAND "pwd\0"
# define EXPORT_COMMAND "export\0"
# define UNSET_COMMAND "unset\0"
# define ENV_COMMAND "env\0"
# define EXIT_COMMAND "exit\0"
# define REDICERTION_TO_FILE ">\0"
# define REDIRECTION_TO_INPUT "<\0"
# define APPEND_REDIRECTION ">>\0"
# define HEREDOC_REDIRECTION "<<\0"
# define NL_FLAG "-n\0"
# define TEMP_FILE "/tmp/Martho_Heredoc_temp.txt\0"
# define FILE_PERMISSIONS 0664

//Might use.
typedef struct s_commands
{
	char	*enviorment; //
	char	**bdir; //
	int		n_pipes; //
	char	***commands; //
	char	**files;
	int		**redirections;
	int		(*fd)[2];
	size_t	*is_bash;
	int		cpipe;
	size_t	ccmd;
	size_t	cfile;
	size_t	cred;
	size_t	credir;
}	t_commands;

enum	e_operations
{
	e_redirection_to_file,
	e_redirection_to_input,
	e_append_redirection,
	e_heredoc_redirection
};
#endif
