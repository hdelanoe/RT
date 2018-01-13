/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:08:18 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 13:37:01 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned long	len;

	if (!s || ft_strcmp(s, "") == 0)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
