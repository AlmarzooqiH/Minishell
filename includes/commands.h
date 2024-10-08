/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:25 by hamad             #+#    #+#             */
/*   Updated: 2024/10/06 17:40:16 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
/*
		 ____     _____                     ______  __  __  ____    ____       
		/\  _`\  /\  __`\  /'\_/`\  /'\_/`\/\  _  \/\ \/\ \/\  _`\ /\  _`\     
		\ \ \/\_\\ \ \/\ \/\      \/\      \ \ \L\ \ \ `\\ \ \ \/\ \ \,\L\_\   
		 \ \ \/_/_\ \ \ \ \ \ \__\ \ \ \__\ \ \  __ \ \ , ` \ \ \ \ \/_\__ \   
		  \ \ \L\ \\ \ \_\ \ \ \_/\ \ \ \_/\ \ \ \/\ \ \ \`\ \ \ \_\ \/\ \L\ \ 
		   \ \____/ \ \_____\ \_\\ \_\ \_\\ \_\ \_\ \_\ \_\ \_\ \____/\ `\____\
		    \/___/   \/_____/\/_/ \/_/\/_/ \/_/\/_/\/_/\/_/\/_/\/___/  \/_____/
*/
# define ECHO_COMMAND "echo\0"
# define CD_COMMAND "cd\0"
# define PWD_COMMAND "pwd\0"
# define EXPORT_COMMAND "export\0"
# define UNSET_COMMAND "unset\0"
# define ENV_COMMAND "env\0"
# define EXIT_COMMAND "exit\0"
# define PIPE "|\0"
# define REDICERTION_TO_FILE ">\0"
# define REDIRECTION_TO_INPUT "<\0"
# define APPEND_REDIRECTION ">>\0"
# define HEREDOC_REDIRECTION "<<\0"
/*
				 ____    __       ______  ____    ____       
				/\  _`\ /\ \     /\  _  \/\  _`\ /\  _`\     
				\ \ \L\_\ \ \    \ \ \L\ \ \ \L\_\ \,\L\_\   
				 \ \  _\/\ \ \  __\ \  __ \ \ \L_L\/_\__ \   
				  \ \ \/  \ \ \L\ \\ \ \/\ \ \ \/, \/\ \L\ \ 
				   \ \_\   \ \____/ \ \_\ \_\ \____/\ `\____\
				    \/_/    \/___/   \/_/\/_/\/___/  \/_____/
*/
# define NL_FLAG "-n\0"
/*
				 ____    __  __  __  __           ____       
				/\  _`\ /\ \/\ \/\ \/\ \  /'\_/`\/\  _`\     
				\ \ \L\_\ \ `\\ \ \ \ \ \/\      \ \,\L\_\   
				 \ \  _\L\ \ , ` \ \ \ \ \ \ \__\ \/_\__ \   
				  \ \ \L\ \ \ \`\ \ \ \_\ \ \ \_/\ \/\ \L\ \ 
				   \ \____/\ \_\ \_\ \_____\ \_\\ \_\ `\____\
				    \/___/  \/_/\/_/\/_____/\/_/ \/_/\/_____/
*/
enum	e_operations
{
	e_pipe,
	e_redirection_to_file,
	e_redirection_to_input,
	e_append_redirection,
	e_heredoc_redirection
};
#endif