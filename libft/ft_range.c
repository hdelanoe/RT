/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:58 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/04 19:31:32 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		*ft_range(int min, int max)
{
	int		*numbers;
	int		i;
	int		j;

	i = min;
	j = 0;
	if (min >= max)
		return (NULL);
	if (!(numbers = (int*)malloc(sizeof(int) * (max - min))))
		return (NULL);
	while (i < max)
	{
		numbers[j] = i;
		j++;
		i++;
	}
	return (numbers);
}
