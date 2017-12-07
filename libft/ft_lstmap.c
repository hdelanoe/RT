/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 03:08:32 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 17:51:32 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*link;

	link = f(lst);
	newlist = link;
	while (lst->next)
	{
		lst = lst->next;
		link->next = f(lst);
		link = link->next;
	}
	return (newlist);
}
