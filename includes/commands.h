/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:25 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 22:40:17 by hamad            ###   ########.fr       */
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
# define STATUS_CODE "$?\0"
# define NL_FLAG "-n\0"
# define TEMP_FILE "/tmp/Martho_Heredoc_temp.txt\0"
# define PERMS 0664

# define SIN STDIN_FILENO
# define SOUT STDOUT_FILENO

# define EF EXIT_FAILURE
# define ES EXIT_SUCCESS

# define GET_STATUS 1
# define SET_STATUS 0

# define INIT_ENVP 0
# define GET_ENVP 1
# define SET_ENVP 2
# define EXIT_ENVP 3
/**
 * @brief This structure will hold the passed in command that will be prepro-
 * -ccessed.
 * @var	c This will hold the tokenized commands.
 * @var	files This will hold the files that we will redirect to.
 * @var	rd This will hold the type of the redirection.
 * @var	is_bash This will hold a value of 1 or 0 if the current command is 
 * in bash or not.
 * @var	p This will hold the pipelines.
 * @var hcfd Has closed file descriptor, this will hold a value {0,1} if
 * the pipe fd on the read/write end has been closed.
 * @var	nscmds This will hold the number of the commands that we have.
 * @var	npipes Will be calculatedd when we init the pipes.
 * @var	nre	Will be calculated when we init the pipes.
 * @var	cpipe Current pipe.
 * @var	ccmd Current command.
 * @var	cf Current file.
 * @var	cr Current redirection.
 * @var	hdp Heredoc position.
 * @var	rtip Redirection to input position.
 * @var	bfdp Beggening fd position.
 * @var	efdp Ending of fd position.
 * @var	a Append flag.
 * @var	t Truncate flag.
 * @var	r Read flag.
 * @var	es Exit status.
 * @var	envp Environment variable.
 * @var	previous_dir Previous directory.
 * @var	bltin Is built in command.
 */
typedef struct s_commands
{
	char	*previous_dir;
	char	***c;
	char	**files;
	char	**envp;
	int		**rd;
	int		*is_bash;
	int		(*p)[2];
	int		(*hcfd)[2];
	int		*fd;
	int		nscmds;
	int		npipes;
	int		nre;
	int		cp;
	int		cc;
	int		cf;
	int		cr;
	int		cfd;
	int		hdp;
	int		rtip;
	int		bfdp;
	int		efdp;
	int		a;
	int		t;
	int		r;
	int		es;
	int		bltin;
}	t_commands;

/**
 * @brief This will hold the type of the redirection.
 * @var e_rtf Redirection to file.
 * @var e_rti Redirection to input.
 * @var e_ar Append redirection.
 * @var e_hdr Heredoc redirection.
 */
enum	e_operations
{
	e_rtf,
	e_rti,
	e_ar,
	e_hdr
};

typedef struct s_expand_vars
{
	int		i;
	int		j;
	char	*result;
}	t_expand_vars;

typedef struct s_quote_info
{
	int		in_quotes;
	int		start_pos;
	char	quote_char;
}	t_quote_info;

#endif
