/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:32:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 08:31:22 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstcat(t_list **lst1, t_list *lst2)
{
	t_list *ptr;
	t_list *begin_ptr;

	if (*lst1 == NULL && lst2 == NULL)
		return (NULL);
	if (*lst1 == NULL)
		*lst1 = lst2;
	ptr = *lst1;
	begin_ptr = ptr;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = lst2;
	return (begin_ptr);
}
