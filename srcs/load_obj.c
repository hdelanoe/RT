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

void		parsing_obj(t_env *e, char ***v, char ***f)
{
	t_vector	tmp;
	t_object	*triangle;
	int			i;

	i = 0;
	while(f[i])
	{
		triangle = init_material();
		if (!(triangle->type = ft_strdup("triangle")))
			exit_rt(1);
		tmp = set_vector(ft_atod(f[i][1]), ft_atod(f[i][2]), ft_atod(f[i][3]));
		triangle->point = set_vector(10 * ft_atod(v[(int)tmp.x - 1][1]), 10 * ft_atod(v[(int)tmp.x - 1][2]), 10 * ft_atod(v[(int)tmp.x - 1][3]));
		triangle->point_2 = set_vector(10 * ft_atod(v[(int)tmp.y - 1][1]), 10 * ft_atod(v[(int)tmp.y - 1][2]), 10 * ft_atod(v[(int)tmp.y - 1][3]));
		triangle->point_3 = set_vector(10 * ft_atod(v[(int)tmp.z - 1][1]), 10 * ft_atod(v[(int)tmp.z - 1][2]), 10 * ft_atod(v[(int)tmp.z - 1][3]));
		add_new_object(&e->object, triangle);
		i++;
	}
}

void		check_line(char *text, t_env *e)
{
	t_parsing	p;
	char	**v[512];
	char	**f[512];
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_bzero(f, sizeof(char***) * 512);
	if ((p.fd = open(text, O_RDONLY)) < 0)
		ft_kill("This file doesn't exist or bad typography.");
	while (get_next_line(p.fd, &p.buff) == 1)
	{
		if (p.buff[0] == 'v' && p.buff[1] == ' ')
		{
			printf("%s\n", p.buff);
			v[i] = ft_strsplit(p.buff, ' ');
			i++;
		}
		if (p.buff[0] == 'f')
		{
			printf("%s\n", p.buff);
			f[j] = ft_strsplit(p.buff, ' ');
			j++;
		}
	}
	ft_printf("Chargement de l'objet'...\n");
	parsing_obj(e, v, f);
	ft_bzero(e->mlx.data, (e->width * e->height) * 4);
	ft_pthread(e, ray_tracer_void);
	ft_printf("Scene chargée.\n");
	close(p.fd);
	free(e->argv_cpy);
}

void		read_obj_files(t_env *e)
{
	DIR				*p;
	struct dirent	*pp;
	char			*tmp;

	p = opendir("./object/");
	ft_printf("\nListe des obj :\n\n");
	if (p != NULL)
	{
		while ((pp = readdir(p)) != NULL)
			ft_printf("%s\n", pp->d_name);
	}
	ft_printf("\nEntrez un objet a charger :\n");
	if (get_next_line(fileno(stdin), &e->argv_cpy) == 1)
	{
		tmp = ft_strdup("./object/");
		e->argv_cpy = ft_strjoin_fre(&tmp, &e->argv_cpy, 1, 1);
		check_line(e->argv_cpy, e);
	}
	else
		ft_printf("Error input obj");
	closedir(p);
	if (e->copy)
		e->copy = NULL;
}
