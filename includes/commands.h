/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:25 by hamad             #+#    #+#             */
/*   Updated: 2024/11/25 22:31:22 by hamad            ###   ########.fr       */
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

# define SIN STDIN_FILENO
# define SOUT STDOUT_FILENO
# define EF EXIT_FAILURE
# define ES EXIT_SUCCESS

/**
 * @brief	This structure will hold the passed in command that will be prepro-
 * -ccessed.
 * @var	enviorment	Will hold the PATH variable.
 * @var	bpath	Will hold the splited PATH variable.
 * @var	cmds	This will hold the tokenized commands.
 * @var	files	This will hold the files that we will redirect to.
 * @var	redir	This will hold the type of the redirection.
 * @var	is_bash	This will hold a value of 1 or 0 if the current command is in bash or not.
 * @var	fd		This will hold the pipelines.
 * @var	nscmds	This will hold the number of the commands that we have.
 * @var	npipes	WIll be calculatedd when we init the pipes.
 * @var	nredir	Will be calculated when we init the pipes.
 * @var	cpipe	Current pipe.
 * @var	ccmd	Current command.
 * @var	cfile	Current file.
 * @var	cred	Current redirection.
 */
typedef struct s_commands
{
	char	*enviorment;
	char	**bpath;
	char	***cmds;
	char	**files;
	int		**redir;
	int		*is_bash;
	int		(*fd)[2];
	int		nscmds;
	int		npipes;
	int		nredir;
	int		cpipe;
	int		ccmd;
	int		cfile;
	int		cred;
}	t_commands;

enum	e_operations
{
	e_redirection_to_file,
	e_redirection_to_input,
	e_append_redirection,
	e_heredoc_redirection
};
#endif
