/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:22:47 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/04/24 14:04:35 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (len != i && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char*)s + len);
	return (NULL);
}
