/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:33:04 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/13 20:34:18 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	unsigned long	i;
	char			*str;

	i = 0;
	str = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			str = (char*)&s[i];
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		str = (char*)&s[i];
	return (str);
}
