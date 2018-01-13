/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 04:16:40 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 20:36:28 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	normalize(double *value)
{
	int		expo;
	double	tmp;

	expo = 0;
	tmp = *value;
	while (tmp >= 1.0)
	{
		tmp /= 10.0;
		++expo;
	}
	while (tmp < 0.1)
	{
		tmp *= 10.0;
		--expo;
	}
	return (expo);
}

static void	ft_expo_accur(double *value, char *buff, int i)
{
	int digit;

	digit = (int)*value;
	buff[i] = digit + '0';
	*value = (*value - digit) * 10.0;
}

static char	*init(double *value)
{
	char	*buff;

	if (!(buff = (char*)ft_memalloc(sizeof(char) * 512)))
		return (NULL);
	if (*value == 0.0)
	{
		buff[0] = '0';
		buff[1] = '\0';
		return (buff);
	}
	if (*value < 0.0)
	{
		buff[0] = '-';
		*value = -*value;
	}
	return (buff);
}

static void	put_accur(double *value, char *buff, int i, int accur)
{
	while (accur > 0.0)
	{
		ft_expo_accur(value, buff, i);
		accur--;
		if (accur == 0 && (int)value >= 5 & buff[i] != '9')
			buff[i]++;
		i++;
	}
}

char		*ft_ftoa(double value, int accur)
{
	int		expo;
	char	*buff;
	int		i;

	i = (value < 0.0) ? 1 : 0;
	buff = init(&value);
	if (value == 0.0)
		return (buff);
	expo = normalize(&value);
	while (expo > 0)
	{
		ft_expo_accur(&value, buff, i);
		expo--;
		i++;
	}
	if (expo < 0)
	{
		buff[i] = '0';
		i++;
		value *= 10.0;
	}
	buff[i] = '.';
	i++;
	put_accur(&value, buff, i, accur);
	return (buff);
}
