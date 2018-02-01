/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:11:27 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:11:27 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_args(char *argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.' && argv[i + 1] == 'r' && argv[i + 2] == 't')
			return (1);
		i++;
	}
	return (0);
}

void		open_close(char *src_file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(src_file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line)
			free(line);
		i++;
	}
	close(fd);
	if (!(i))
		ft_kill("Bad file. Please enter a valid scene to read.");
}

void	exit_rt(int flag)
{
	if (flag == 1)
	{
		ft_putendl("Error in malloc");
		exit(1);
	}
}
