/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:24:39 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/05/05 04:14:48 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static void	set_rest(char **rest, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(*rest, buff);
	if (*rest)
		free(*rest);
	*rest = tmp;
}

static int	get_line(char **line, char **rest)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = ft_strchr(*rest, '\n')))
	{
		*line = ft_strsub(*rest, 0, ft_strlen(*rest) - ft_strlen(ptr));
		tmp = ft_strdup(ptr + 1);
		free(*rest);
		*rest = tmp;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*rest = 0;
	char		buff[BUFF_SIZE + 1];
	int			i;

	if ((fd < 0 || !line || read(fd, buff, 0) < 0))
		return (-1);
	if (rest && get_line(line, &rest))
		return (1);
	while ((i = read(fd, buff, BUFF_SIZE)) != 0)
	{
		buff[i] = '\0';
		set_rest(&rest, buff);
		if (get_line(line, &rest))
			return (1);
	}
	if (rest == NULL || rest[0] == '\0')
		return (0);
	*line = ft_strdup(rest);
	free(rest);
	rest = NULL;
	return (1);
}
