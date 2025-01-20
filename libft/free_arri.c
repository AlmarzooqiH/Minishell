/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:06:07 by hamad             #+#    #+#             */
/*   Updated: 2025/01/20 13:58:04 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_arri(int **arri, int size)
{
	int	i;

	i = 0;
	while (i < size && arri[i] != NULL)
	{
		free(arri[i]);
		i++;
	}
	free(arri);
}
