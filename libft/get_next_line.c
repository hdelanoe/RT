/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:49:05 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/25 18:40:54 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_storage(char **stocker, char *target, char **line)
{
	t_stock		tool;

	tool.save = *stocker;
	if (target != NULL)
	{
		tool.rest = ft_strchr(target, '\n');
		*tool.rest = '\0';
		*line = ft_strjoin(tool.save, target);
		*stocker = ft_strdup(tool.rest + 1);
	}
	else
	{
		tool.rest = ft_strchr(*stocker, '\n');
		*tool.rest = '\0';
		*line = ft_strdup(*stocker);
		*stocker = ft_strdup(tool.rest + 1);
	}
	free(tool.save);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	t_stock			tool;
	static char		*stocker = NULL;

	if (BUFF_SIZE <= 0 || (!line) || fd < 0)
		return (-1);
	stocker = (!stocker) ? ft_strnew(0) : stocker;
	if (ft_strchr(stocker, '\n') != 0)
		return (ft_storage(&stocker, NULL, line));
	while ((tool.ret = read(fd, tool.buff, BUFF_SIZE)))
	{
		if (tool.ret < 0)
			return (-1);
		tool.buff[tool.ret] = '\0';
		if (ft_strchr(tool.buff, '\n') != 0)
			return (ft_storage(&stocker, tool.buff, line));
		tool.tmp = stocker;
		stocker = ft_strjoin(stocker, tool.buff);
		free(tool.tmp);
	}
	if (stocker != 0 && ft_strlen(stocker) != 0 && (*line = ft_strdup(stocker)))
	{
		ft_strdel(&stocker);
		return (1);
	}
	return (0);
}
