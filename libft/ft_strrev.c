/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 01:44:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 09:19:27 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	char	r;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		r = str[i];
		str[i] = str[j];
		str[j] = r;
		j--;
		i++;
	}
	return (str);
}
