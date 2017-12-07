/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 21:35:03 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/06 03:24:52 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*str;
	size_t			i;

	i = 0;
	dest = (unsigned char*)dst;
	str = (unsigned char*)src;
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	return (dst);
}
