/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:21:59 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/05/18 09:40:52 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	a;
	char			*str;

	i = 0;
	a = (unsigned char)c;
	str = (char*)s;
	while (i < n)
	{
		str[i] = a;
		i++;
	}
	return (s);
}
