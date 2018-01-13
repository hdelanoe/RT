/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:24:12 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/04/16 15:28:46 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static size_t	ft_end(const char *s)
{
	size_t i;

	i = ft_strlen(s);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
			&& i > 0)
		i--;
	return (i);
}

char			*ft_strtrim(const char *s)
{
	size_t	i;
	size_t	j;

	i = ft_start(s);
	j = ft_end(s);
	if (i > j)
		return ("");
	else
		return (ft_strsub(s, i, j - i + 1));
}
