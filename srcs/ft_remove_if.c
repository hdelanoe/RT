/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:48:03 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/31 12:48:05 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			cmp(int a, int b)
{
	if (a == b)
		return (0);
	return (1);
}

t_object	*ft_remove_begin(t_object **prev, t_object **ptr)
{
	t_object *begin_object;

	*prev = NULL;
	begin_object = (*ptr)->next;
	free((*ptr)->type);
	free(*ptr);
	*ptr = begin_object;
	return (begin_object);
}

void		ft_object_remove_if(t_object **beg_obj, int data_ref, int (*cmp)())
{
	t_object *ptr;
	t_object *prev;

	ptr = *beg_obj;
	prev = NULL;
	while (ptr)
	{
		if (cmp(ptr->id, data_ref) == 0)
		{
			if (ptr == *beg_obj)
				*beg_obj = ft_remove_begin(&prev, &ptr);
			else
			{
				prev->next = ptr->next;
				free(ptr);
				ptr = prev->next;
			}
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}
