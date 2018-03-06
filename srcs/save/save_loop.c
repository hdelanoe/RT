/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:33:07 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/20 18:33:27 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		put_arealight_file(t_object *area, int fd)
{
	put_type_object(area->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord_1", &area->point, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_2", &area->point_2, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_3", &area->point_3, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_4", &area->point_4, fd);
	write(fd, "\t\t", 2);
	put_color(&area->color, fd);
	write(fd, "\t\t}\n\t", 5);
}

void		put_paraboloid_file(t_object *paraboloid, int fd)
{
	put_type_object(paraboloid->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &paraboloid->center, fd);
	write(fd, "\t\t", 2);
	put_axis("axis", &paraboloid->axis, fd);
	write(fd, "\n\t\t", 3);
	put_int("length", paraboloid->lenght_max, fd);
	write(fd, "\t\t", 2);
	put_color(&paraboloid->color, fd);
	put_material(fd, paraboloid);
	write(fd, "\t\t}\n\t", 5);
}

void		put_obj_loop(int fd, t_object *tmp)
{
	if (!ft_strcmp("quad", tmp->type))
		put_quad_file(tmp, fd);
	if (!ft_strcmp("plane", tmp->type))
		put_plane_file(tmp, fd);
	if (!ft_strcmp("cone", tmp->type))
		put_cone_file(tmp, fd);
	if (!ft_strcmp("sphere", tmp->type))
		put_sphere_file(tmp, fd);
	if (!ft_strcmp("cylinder", tmp->type))
		put_cylinder_file(tmp, fd);
	if (!ft_strcmp("cube", tmp->type))
		put_cube_file(tmp, fd);
	if (!ft_strcmp("glass", tmp->type))
		put_glass_file(tmp, fd);
	if (!ft_strcmp("triangle", tmp->type))
		put_triangle_file(tmp, fd);
	if (!ft_strcmp("pyramide", tmp->type))
		put_pyramide_file(tmp, fd);
	if (!ft_strcmp("area_light", tmp->type))
		put_arealight_file(tmp, fd);
	if (!ft_strcmp("paraboloid", tmp->type))
		put_paraboloid_file(tmp, fd);
}

void		put_double(char *name, double color, int fd)
{
	char *tmp;
	char *tmp_2;

	put_type_object(name, fd);
	if (color < 1 && color > 0)
	{
		tmp = ft_strdup("0.");
		tmp_2 = ft_itoa(color * 10);
		tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	}
	else
		tmp = ft_itoa(color);
	tmp_2 = ft_strdup("\"");
	tmp = ft_strjoin_fre(&tmp_2, &tmp, 1, 1);
	tmp_2 = ft_strdup("\"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void		put_cam_win_file(t_env *e, int fd)
{
	put_coord("camera_origin", &e->camera.origin, fd);
	write(fd, "\t", 1);
	put_coord("camera_lookat", &e->lookat, fd);
	write(fd, "\t", 1);
	put_int("window_width", (int)e->width, fd);
	write(fd, "\t", 1);
	put_int("window_height", (int)e->height, fd);
	write(fd, "\t", 1);
	put_int("recursion", (int)e->recursion, fd);
	write(fd, "\t", 1);
}
