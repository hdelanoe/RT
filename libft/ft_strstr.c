/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:40:52 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 21:25:10 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	n;
	size_t	i;
	char	*str;

	n = ft_strlen(little);
	i = 0;
	str = (char*)big;
	if (n == 0)
		return (str);
	while (str[i] != '\0')
	{
		if (ft_strncmp(&str[i], little, n) == 0)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
