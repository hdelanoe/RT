/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 22:47:06 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/05 22:07:32 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*str;
	size_t	i;

	dest = (char*)dst;
	str = (char*)src;
	i = 0;
	if (str < dest)
	{
		while (len--)
			dest[len] = str[len];
	}
	else
		ft_memcpy(dest, str, len);
	return (dest);
}
