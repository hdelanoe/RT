/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:14:28 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/07 22:02:22 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static char		*n_is_positive(int n)
{
	int		len;
	int		tmp;
	char	*str;

	len = 0;
	tmp = n;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		len++;
	}
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

static char		*n_is_negative(int n)
{
	int		len;
	int		tmp;
	char	*str;

	len = 1;
	n = -n;
	tmp = n;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		len++;
	}
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
		return (n_is_negative(n));
	else
		return (n_is_positive(n));
}
