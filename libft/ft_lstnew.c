/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:32:24 by hamalmar          #+#    #+#             */
/*   Updated: 2023/11/11 14:38:16 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ll;

	ll = (t_list *)malloc(sizeof(t_list));
	if (ll == 0)
		return (0);
	ll->content = content;
	ll->next = 0;
	return (ll);
}
