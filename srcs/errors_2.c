/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:11:27 by notraore          #+#    #+#             */
/*   Updated: 2018/03/01 21:29:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_arg(t_parsing *p, char *type)
{
	if (p->directory != NULL)
	{
		while ((p->name = readdir(p->directory)) != NULL)
			if (p->name->d_name[0] != '.')
				print_list_obj(p->name->d_name, p->tmp_2);
		closedir(p->directory);
	}
	else
	{
		if (!ft_strcmp(p->tmp_2, "./object"))
		{
			ft_printf("RT did not find the %s\n", type);
			return (0);
		}
		while (p->tmp_2[++p->i])
		{
			if (p->tmp_2[p->i] == '.' &&
				((p->tmp_2[p->i + 1] == 'r' && p->tmp_2[p->i + 2] == 't')
				|| (p->tmp_2[p->i + 1] == 'o' && p->tmp_2[p->i + 2] == 'b'
				&& p->tmp_2[p->i + 3] == 'j')))
				ft_printf("%s\n", &p->tmp_2[9]);
		}
	}
	return (1);
}

int		print_list_scenes(char *file, char *path)
{
	t_parsing	p;

	p.i = 8;
	p.tmp = ft_strjoin(path, "/");
	p.tmp_2 = ft_strjoin_fre(&p.tmp, &file, 1, 0);
	p.directory = opendir(p.tmp_2);
	check_arg(&p, "scenes");
	ft_strdel(&p.tmp_2);
	return (1);
}

int		print_list_obj(char *file, char *path)
{
	t_parsing	p;

	p.i = 8;
	p.tmp = ft_strjoin(path, "/");
	p.tmp_2 = ft_strjoin_fre(&p.tmp, &file, 1, 0);
	p.directory = opendir(p.tmp_2);
	check_arg(&p, "object");
	ft_strdel(&p.tmp_2);
	return (1);
}

void	exit_rt(int flag)
{
	if (flag == 1)
	{
		ft_putendl("Error in malloc");
		exit(1);
	}
}

void	free_2star(char ***mem)
{
	int i;
	int j;

	i = -1;
	while (mem[++i])
	{
		j = -1;
		while (mem[i][++j])
		{
			free(mem[i][j]);
			mem[i] = NULL;
		}
	}
}
