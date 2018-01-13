/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 08:32:24 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 09:16:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **lst)
{
	t_list	*prev;
	t_list	*next;

	if ((*lst) == NULL)
		return ;
	prev = NULL;
	while ((*lst) != NULL)
	{
		next = (*lst)->next;
		(*lst)->next = prev;
		prev = (*lst);
		(*lst) = next;
	}
	(*lst) = prev;
}
