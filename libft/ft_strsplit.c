/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:10:15 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/05 01:31:28 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_nbwords(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s != c)
		{
			i = 0;
			if (!(tab[j] =
			(char*)malloc(sizeof(char) * (ft_lenwords(s, c) + 1))))
				return (NULL);
			while (*s && *s != c)
				tab[j][i++] = *s++;
			tab[j++][i] = '\0';
		}
	}
	tab[j] = 0;
	return (tab);
}
