/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:15:21 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/26 22:15:23 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_obj(t_parsing *p)
{
	p->i = -1;
	while (++p->i < 4096)
	{
		p->j = -1;
		while (p->f[p->i] && p->f[p->i][++p->j])
			free(p->f[p->i][p->j]);
		p->j = -1;
		while (p->v[p->i] && p->v[p->i][++p->j])
			free(p->v[p->i][p->j]);
		free(p->f[p->i]);
		free(p->v[p->i]);
	}
}

int		read_obj(t_env *e, t_parsing *p, char *text)
{
	int ret;

	ret = 0;
	if ((p->fd = open(text, O_RDONLY)) < 0)
		return (ret);
	ft_printf("Loading object...\n");
	while (get_next_line(p->fd, &p->buff) == 1)
	{
		if (p->i >= 4096 || p->j >= 4096)
		{
			free(e->argv_cpy);
			ft_printf("Sorry, %s is too big!\n", text);
			return (ret);
		}
		if (p->buff[0] == 'v' && p->buff[1] == ' ')
			p->v[++p->i] = ft_strsplit(p->buff, ' ');
		if (p->buff[0] == 'f')
			p->f[++p->j] = ft_strsplit(p->buff, ' ');
		ft_strdel(&p->buff);
	}
	close(p->fd);
	ret = parsing_obj(e, p->v, p->f);
	free_obj(p);
	return (ret);
}

int		check_line(char *text, t_env *e)
{
	t_parsing	p;

	p.i = -1;
	p.j = -1;
	ft_bzero(p.f, sizeof(char***) * 4096);
	ft_bzero(p.v, sizeof(char***) * 4096);
	if (!ft_strcmp(ft_strstr(text, ".rt"), ".rt"))
	{
		if (!parsing(e, text))
			return (0);
		create_tree(e, &e->stock);
		ft_strdel(&e->stock);
	}
	else if (!ft_strcmp(ft_strstr(text, ".obj"), ".obj")
		&& !read_obj(e, &p, text))
	{
		ft_printf("Sorry, %s is not a valid object\n", text);
		return (0);
	}
	ft_bzero(e->mlx.data, (e->width * e->height) * 4);
	e->loading = 0;
	ft_pthread(e, ray_tracer_void);
	ft_printf("Object loaded.\n");
	ft_strdel(&e->argv_cpy);
	return (1);
}

int		read_obj_files(t_env *e)
{
	char			*tmp;

	ft_printf("\nListe des obj :\n\n");
	if (!print_list_obj("object", "."))
		return (0);
	e->loading = 0;
	ft_printf("\nPlease choose an object to load :\n");
	if (get_next_line(fileno(stdin), &e->argv_cpy) == 1)
	{
		if (!e->argv_cpy[0])
			return (0);
		tmp = ft_strdup("./object/");
		e->argv_cpy = ft_strjoin_fre(&tmp, &e->argv_cpy, 1, 1);
		if (!check_line(e->argv_cpy, e))
		{
			ft_strdel(&e->argv_cpy);
			return (0);
		}
		ft_strdel(&e->argv_cpy);
	}
	else
		ft_printf("Error input obj");
	if (e->copy)
		e->copy = NULL;
	return (1);
}

void	check_load(t_env *e)
{
	if (e->loading == 1)
		return ;
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->img_bat, e->width / 4 - 40, e->height / 3);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr,
	(e->width / 2.8), (e->height / 4),
	0xFFFFFF, "At least someone is working...");
	mlx_do_sync(e->mlx.mlx_ptr);
}
