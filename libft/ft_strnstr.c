/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:08:43 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 14:40:30 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)big;
	if (ft_strlen(little) == 0)
		return (str);
	if (ft_strlen(big) == 0 || len < ft_strlen(little))
		return (NULL);
	while (i <= len - ft_strlen(little) && str[i] != '\0')
	{
		if (ft_strncmp(&str[i], little, ft_strlen(little)) == 0)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
