/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:11:27 by notraore          #+#    #+#             */
/*   Updated: 2018/03/01 21:29:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		open_close(char *src_file, t_env *e)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	e->pars_flag = 1;
	fd = open(src_file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line)
			free(line);
		i++;
	}
	close(fd);
	if ((!i) && e->pars_flag == 1)
	{
		ft_printf("Bad file. Please enter a valid scene to read.\n");
		return (1);
	}
	else if (!i)
	{
		ft_kill("Bad file. Please enter a valid scene to read.");
		return (1);
	}
	return (0);
}
