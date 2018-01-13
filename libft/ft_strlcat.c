/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:48:42 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/13 12:10:19 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	dlen;
	unsigned long	slen;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen + 1 > size || size == 0)
		return (size + slen);
	while (i < size - dlen - 1 && src[i] != '\0')
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if (dlen + i > size)
		return (slen + size);
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
