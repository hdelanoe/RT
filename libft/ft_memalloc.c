/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 17:17:56 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 01:46:50 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*src;

	if (!(src = (void*)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(src, size);
	return (src);
}
