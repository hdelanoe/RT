/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:08:13 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/22 18:08:15 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_fre(char **s1, char **s2, int b1, int b2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2));
	i = 0;
	j = 0;
	while ((*s1) && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	if ((*s1) && b1)
		free(*s1);
	while ((*s2) && (*s2)[j])
	{
		str[i] = (*s2)[j];
		j++;
		i++;
	}
	if ((*s2) && b2)
		free(*s2);
	return (str);
}