/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:07:43 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 09:55:24 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisalpha(const char *str)
{
	int i;

	i = 0;
	while (ft_isalpha(str[i] == 1))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}
