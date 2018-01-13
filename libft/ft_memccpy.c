/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:26:58 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/13 12:18:43 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned long	i;
	unsigned char	a;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	a = (unsigned char)c;
	s1 = (unsigned char*)dest;
	s2 = (unsigned char*)src;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == a)
			return (&s1[i + 1]);
		i++;
	}
	return (NULL);
}
