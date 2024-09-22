/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:54:12 by hamalmar          #+#    #+#             */
/*   Updated: 2023/12/07 22:09:04 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current_l_node;
	t_list	*current_head;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	head = ft_lstnew((*f)(lst->content));
	if (head == 0)
		return (0);
	current_l_node = lst->next;
	current_head = head;
	while (current_l_node)
	{
		current_head->next = ft_lstnew((*f)(current_l_node->content));
		if (current_head->next == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		current_head = current_head->next;
		current_l_node = current_l_node->next;
	}
	return (head);
}
