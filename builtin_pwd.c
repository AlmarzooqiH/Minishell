/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:12:18 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 18:26:40 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will simulate the behavior of pwd.
 * @param None.
 * @return Void.
 */
void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"));
	printf("%s\n", pwd);
	free(pwd);
	gs_status(GET_STATUS, SET_STATUS);
}
