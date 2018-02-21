/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:23:28 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/20 18:29:12 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		put_axis(char *name, t_vector *point, int fd)
{
	char *tmp;
	char *tmp_2;

	put_type_object(name, fd);
	check_value_point(point);
	tmp = ft_strdup("{\"x\": \"");
	tmp_2 = ft_itoa(point->x);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"y\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1 ,1);
	tmp_2 = ft_itoa(point->y);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"z\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_itoa(point->z);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\"},\n");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void		put_int(char *name, int i, int fd)
{
	char *tmp;
	char *tmp_2;

	put_type_object(name, fd);
	tmp = ft_strdup("\"");
	tmp_2 = ft_itoa(i);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\"\n");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void		put_coord(char *name, t_vector *point, int fd)
{
	put_type_object(name, fd);
	write(fd, "{", 1);
	put_xyz(point, fd);
}

void		put_cylinder_file(t_object *cylinder, int fd)
{
	put_type_object(cylinder->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &cylinder->center, fd);
	put_axis("axis", &cylinder->axis, fd);
	put_int("radius", cylinder->radius, fd);
	put_int("length", cylinder->lenght_max, fd);
	put_color(&cylinder->color, fd);
	write(fd, "}\n", 2);
}

void		put_cube_file(t_object *cube, int fd)
{
	put_type_object(cube->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &cube->center, fd);
	put_int("width", cube->lenght_max, fd);
	put_int("length", cube->tangent, fd);
	put_int("height", cube->radius, fd);
	put_axis("axis", &cube->axis, fd);
	put_color(&cube->color, fd);
	write(fd, "}\n", 2);
}
