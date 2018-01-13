/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:26:04 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/15 14:57:36 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned long	i;
	unsigned char	a;
	char			*str;

	i = 0;
	a = (unsigned char)c;
	str = (char*)s;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	else
		return (NULL);
}
