/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:55:32 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/02 23:57:23 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dest;
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	len = ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		len--;
		if (s[i] == '\0')
			return ("\0");
	}
	if (!(dest = ft_strnew(len)))
		return (NULL);
	j = 0;
	while (j < len)
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}
