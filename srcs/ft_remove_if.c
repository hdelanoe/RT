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

#include "../includes/rt.h"

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
	(*ptr)->next = NULL;
	free((*ptr)->type);
	free(*ptr);
	(*ptr) = NULL;
	*ptr = begin_object;
	return (begin_object);
}

void		ft_remove_after(t_object **prev, t_object **ptr)
{
	(*prev)->next = (*ptr)->next;
	free((*ptr)->type);
	free((*ptr));
	(*ptr) = NULL;
	(*ptr) = (*prev)->next;
}

void		ft_object_remove_if(t_object **beg_obj, int data_ref, int (*cmp)())
{
	t_object *ptr;
	t_object *prev;

	ptr = *beg_obj;
	while (ptr)
	{
		if (data_ref == -999 || cmp(ptr->id, data_ref) == 0)
		{
			if (ptr->sub_object)
				ft_object_remove_if(&ptr->sub_object, -999, (*cmp));
			if (ptr == *beg_obj)
				*beg_obj = ft_remove_begin(&prev, &ptr);
			else
				ft_remove_after(&prev, &ptr);
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}
