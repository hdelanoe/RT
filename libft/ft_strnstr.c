/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:39:10 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 16:34:43 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	if (!*little)
		return ((char *)big);
	len_little = ft_strlen(little);
	while (big[i] != '\0' && (i + len_little) <= len)
	{
		if (ft_strncmp(big + i, little, len_little) == 0)
			return ((char*)big + i);
		i++;
	}
	return (NULL);
}
