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

#include "../includes/rt.h"

void		put_axis(char *name, t_vector *point, int fd)
{
	char *tmp;
	char *tmp_2;

	put_type_object(name, fd);
	check_value_point(&point->x);
	check_value_point(&point->y);
	check_value_point(&point->z);
	tmp = ft_strdup("{\"x\": \"");
	tmp_2 = ft_itoa(point->x);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"y\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_itoa(point->y);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"z\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_itoa(point->z);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\"},");
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
	tmp_2 = ft_strdup("\"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
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
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &cylinder->center, fd);
	write(fd, "\t\t", 2);
	put_axis("axis", &cylinder->axis, fd);
	write(fd, "\n\t\t", 3);
	put_int("radius", cylinder->radius, fd);
	write(fd, "\t\t", 2);
	put_int("length", cylinder->lenght_max, fd);
	write(fd, "\t\t", 2);
	put_color(&cylinder->color, fd);
	put_material(fd, cylinder);
	write(fd, "\t\t}\n\t", 5);
}

void		put_cube_file(t_object *cube, int fd)
{
	put_type_object(cube->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &cube->center, fd);
	write(fd, "\t\t", 2);
	put_int("width", cube->lenght_max, fd);
	write(fd, "\t\t", 2);
	put_int("length", cube->tangent, fd);
	write(fd, "\t\t", 2);
	put_int("height", cube->radius, fd);
	write(fd, "\t\t", 2);
	put_axis("axis", &cube->axis, fd);
	write(fd, "\n\t\t", 3);
	put_color(&cube->color, fd);
	put_material(fd, cube);
	write(fd, "\t\t}\n\t", 5);
}
