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

#include "../includes/rt.h"

void		put_plane_file(t_object *plane, int fd)
{
	put_type_object(plane->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &plane->point, fd);
	write(fd, "\t\t", 2);
	put_axis("normal", &plane->normal, fd);
	write(fd, "\n\t\t", 3);
	put_color(&plane->color, fd);
	put_material(fd, plane);
	write(fd, "\t\t}\n\t", 5);
}

void		put_light_file(t_light *light, int fd)
{
	put_type_object(light->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &light->origin, fd);
	write(fd, "\t\t", 2);
	put_color(&light->color, fd);
	write(fd, "\t\t}\n\t", 5);
}

void		put_cone_file(t_object *cone, int fd)
{
	put_type_object(cone->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &cone->center, fd);
	write(fd, "\t\t", 2);
	put_double("tangent", cone->tangent, fd);
	write(fd, "\t\t", 2);
	put_int("maxlength", cone->lenght_max, fd);
	write(fd, "\t\t", 2);
	put_int("minlength", cone->radius, fd);
	write(fd, "\t\t", 2);
	put_axis("axis", &cone->axis, fd);
	write(fd, "\n\t\t", 3);
	put_color(&cone->color, fd);
	put_material(fd, cone);
	write(fd, "\t\t}\n\t", 5);
}

void		put_quad_file(t_object *quad, int fd)
{
	put_type_object(quad->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord_1", &quad->point, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_2", &quad->point_2, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_3", &quad->point_3, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_4", &quad->point_4, fd);
	write(fd, "\t\t", 2);
	put_color(&quad->color, fd);
	put_material(fd, quad);
	write(fd, "\t\t}\n\t", 5);
}

void		put_sphere_file(t_object *sphere, int fd)
{
	put_type_object(sphere->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &sphere->center, fd);
	write(fd, "\t\t", 2);
	put_int("radius", sphere->radius, fd);
	if (sphere->cap == 1)
	{
		put_axis("plan_cut", &sphere->normal, fd);
		write(fd, "\n\t\t", 3);
	}
	else
		write(fd, "\t\t", 2);
	put_color(&sphere->color, fd);
	put_material(fd, sphere);
	write(fd, "\t\t}\n\t", 5);
}
