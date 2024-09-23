/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:22:44 by hamad             #+#    #+#             */
/*   Updated: 2024/09/23 17:57:30 by hamad            ###   ########.fr       */
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
# include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include "error.h"
#endif