/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:25 by hamad             #+#    #+#             */
/*   Updated: 2024/12/29 17:49:14 by hamad            ###   ########.fr       */
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
# define PERMS 0664

# define SIN STDIN_FILENO
# define SOUT STDOUT_FILENO
# define EF EXIT_FAILURE
# define ES EXIT_SUCCESS

/**
 * @brief This structure will hold the passed in command that will be prepro-
 * -ccessed.
 * @var	enviorment Will hold the PATH variable.
 * @var	bpath Will hold the splited PATH variable.
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
 */
typedef struct s_commands
{
	char	*enviorment;
	char	*previous_dir;
	char	**bpath;
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
typedef struct s_minishell_state
{
	char	**envp;
	int		exit_status;
	char		*previous_dir;
}	t_minishell_state;
#endif
