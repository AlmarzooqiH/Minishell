/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:43:25 by hamalmar          #+#    #+#             */
/*   Updated: 2023/12/07 22:05:31 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	int		size;
	t_list	*current_node;

	if (!lst || !del)
		return ;
	size = ft_lstsize(*lst);
	while (size > 0)
	{
		current_node = *lst;
		*lst = current_node->next;
		del(current_node->content);
		free(current_node);
		size--;
	}
}
