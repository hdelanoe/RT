/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:32:13 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/05/05 06:40:40 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_nbstr(const char *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb++;
		i++;
	}
	return (nb);
}

static char		**ft_init(const char *s, char c)
{
	char	**tab;

	tab = (char**)malloc(sizeof(char*) * (ft_nbstr(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	return (tab);
}

char			**ft_strsplit(const char *s, char c)
{
	size_t	i;
	char	**tab;
	size_t	start;
	size_t	nb;

	i = 0;
	if (!(tab = ft_init(s, c)))
		return (NULL);
	nb = 0;
	start = 0;
	while (i < ft_strlen(s) || nb < ft_nbstr(s, c))
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (!(tab[nb] = ft_strsub(s, start, i - start)))
			return (NULL);
		nb++;
	}
	tab[nb] = NULL;
	return (tab);
}
