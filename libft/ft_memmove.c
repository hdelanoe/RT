/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:35:06 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 15:20:03 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	if (dest == src || n == 0)
		return (dest);
	i = 0;
	s1 = (unsigned char*)dest;
	s2 = (unsigned char*)src;
	if (src < dest)
	{
		i = n - 1;
		while (i > 0)
		{
			s1[i] = s2[i];
			i--;
		}
		s1[i] = s2[i];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
