/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:22:07 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/20 18:31:12 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		put_plane_file(t_object *plane, int fd)
{
	put_type_object(plane->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &plane->point, fd);
	put_axis("normal", &plane->normal, fd);
	put_color(&plane->color, fd);
	write(fd, "}\n", 2);
}

void		put_light_file(t_light *light, int fd)
{
	put_type_object(light->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &light->origin, fd);
	put_color(&light->color, fd);
	write(fd, "}\n", 2);
}

void		put_cone_file(t_object *cone, int fd)
{
	put_type_object(cone->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &cone->center, fd);
	put_double("tangent", cone->tangent, fd);
	put_int("maxlength", cone->lenght_max, fd);
	put_int("minlength", cone->radius, fd);
	put_axis("axis", &cone->axis, fd);
	put_color(&cone->color, fd);
	write(fd, "}\n", 2);
}

void		put_quad_file(t_object *quad, int fd)
{
	put_type_object(quad->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord_1", &quad->point, fd);
	put_coord("coord_2", &quad->point_2, fd);
	put_coord("coord_3", &quad->point_3, fd);
	put_coord("coord_4", &quad->point_4, fd);
	put_color(&quad->color, fd);
	write(fd, "}\n", 2);
}

void		put_sphere_file(t_object *sphere, int fd)
{
	put_type_object(sphere->type, fd);
	write(fd, "{\n", 2);
	put_coord("coord", &sphere->center, fd);
	put_int("radius", sphere->radius, fd);
	if (sphere->cap == 1)
		put_axis("plan_cut", &sphere->normal, fd);
	put_color(&sphere->color, fd);
	write(fd, "}\n", 2);
}
