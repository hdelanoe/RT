/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:58:30 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 19:15:01 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strrev(char *s)
{
	int		a;
	int		len;
	int		i;

	i = 0;
	a = 0;
	len = 0;
	while (s[len])
		len++;
	len--;
	while (i < len)
	{
		a = s[i];
		s[i] = s[len];
		s[len] = a;
		i++;
		len--;
	}
	return (s);
}
