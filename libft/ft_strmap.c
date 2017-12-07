/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:52:07 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/04/30 22:37:18 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dest;
	size_t	i;

	if (!(dest = (char*)malloc(sizeof(char) * ft_strlen((char*)s) + 1)))
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		dest[i] = (*f)(*s);
		i++;
		s++;
	}
	dest[i] = '\0';
	return (dest);
}
