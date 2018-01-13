/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 13:42:00 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 11:06:53 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list_cpy;
	t_list	*tmp2;
	t_list	*new_lst;

	if (lst == NULL)
		return (NULL);
	list_cpy = ft_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
	if (list_cpy == NULL)
		return (NULL);
	lst = lst->next;
	tmp2 = list_cpy;
	while (lst != NULL)
	{
		new_lst = ft_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
		if (new_lst == NULL)
			return (NULL);
		lst = lst->next;
		tmp2->next = new_lst;
		tmp2 = tmp2->next;
	}
	return (list_cpy);
}
