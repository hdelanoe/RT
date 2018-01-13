/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 11:37:34 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/13 18:46:11 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	utoalen(unsigned int n, int base)
{
	int i;

	i = 1;
	while (n / base > 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char		goa(unsigned int n)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = "0123456789abcdef";
	while (i < n)
		i++;
	return (str[i]);
}

char		*ft_utoa(unsigned int n, int base)
{
	char	*str;
	int		i;

	i = utoalen(n, base);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	while (n / base > 0)
	{
		str[i] = goa(n % base);
		n /= base;
		i--;
	}
	str[i] = goa(n % base);
	return (str);
}
