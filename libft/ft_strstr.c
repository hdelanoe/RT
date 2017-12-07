/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:33:38 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/02 15:09:01 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(little);
	if (!*little)
		return ((char*)big);
	while (big[i])
	{
		while (little[j] == big[i + j])
		{
			if (j == len - 1)
				return ((char*)big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
