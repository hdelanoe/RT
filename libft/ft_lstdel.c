/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 13:25:00 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/15 16:06:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (*alst == NULL)
		return ;
	while ((*alst) != NULL)
	{
		(*del)((*alst)->content, (*alst)->content_size);
		tmp = (*alst);
		(*alst) = (*alst)->next;
		free(tmp);
		tmp = NULL;
	}
}
