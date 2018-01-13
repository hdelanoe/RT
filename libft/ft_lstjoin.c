/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:01:19 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 08:33:27 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstjoin(t_list *lst1, t_list *lst2)
{
	t_list	*list_merge;
	t_list	*begin_list_merge;

	list_merge = lst1;
	begin_list_merge = list_merge;
	while (lst1 != NULL)
	{
		list_merge = (t_list*)malloc(sizeof(list_merge));
		if (list_merge == NULL)
			return (NULL);
		list_merge = lst1;
		lst1 = lst1->next;
		list_merge = list_merge->next;
	}
	while (lst2 != NULL)
	{
		list_merge = (t_list*)malloc(sizeof(list_merge));
		if (list_merge == NULL)
			return (NULL);
		list_merge = lst2;
		lst2 = lst2->next;
		list_merge = list_merge->next;
	}
	return (begin_list_merge);
}
