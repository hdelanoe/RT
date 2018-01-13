/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:58:56 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 08:33:43 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstfind(t_list *begin_list, void *content_ref, int (*cmp)())
{
	while (begin_list != NULL)
	{
		if (cmp(begin_list->content, content_ref) == 0)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (0);
}
