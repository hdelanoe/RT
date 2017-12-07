/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 21:57:22 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/04/24 14:07:30 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memccpy(void *restrict dst,
const void *restrict src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*str;
	size_t			i;
	unsigned char	a;

	i = 0;
	a = (unsigned char)c;
	dest = (unsigned char*)dst;
	str = (unsigned char*)src;
	while (i < n)
	{
		dest[i] = str[i];
		if (str[i] == a)
		{
			i++;
			return (dst + i);
		}
		i++;
	}
	return (NULL);
}
