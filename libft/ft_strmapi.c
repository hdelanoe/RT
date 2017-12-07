/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 19:17:05 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 19:56:57 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	size_t			i;
	unsigned int	j;

	if (!(dest = (char*)malloc(sizeof(char) * (ft_strlen((char*)s) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (*s)
	{
		dest[i] = (*f)(j, *s);
		i++;
		j++;
		s++;
	}
	dest[i] = '\0';
	return (dest);
}
