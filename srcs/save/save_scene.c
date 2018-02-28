/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:33:07 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/20 18:33:27 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		put_glass_file(t_object *glass, int fd)
{
	put_type_object(glass->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord", &glass->center, fd);
	write(fd, "\t\t", 2);
	put_axis("axis", &glass->axis, fd);
	write(fd, "\n\t\t", 3);
	put_int("length", glass->lenght_max, fd);
	write(fd, "\t\t", 2);
	put_color(&glass->color, fd);
	put_material(fd, glass);
	write(fd, "\t\t}\n\t", 5);
}

void		put_triangle_file(t_object *triangle, int fd)
{
	put_type_object(triangle->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord_1", &triangle->point, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_2", &triangle->point_2, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_3", &triangle->point_3, fd);
	write(fd, "\t\t", 2);
	put_color(&triangle->color, fd);
	put_material(fd, triangle);
	write(fd, "\t\t}\n\t", 5);
}

void		put_pyramide_file(t_object *pyramide, int fd)
{
	put_type_object(pyramide->type, fd);
	write(fd, "{\n\t\t", 4);
	put_coord("coord_1", &pyramide->point, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_2", &pyramide->point_2, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_3", &pyramide->point_3, fd);
	write(fd, "\t\t", 2);
	put_coord("coord_4", &pyramide->point_4, fd);
	write(fd, "\t\t", 2);
	put_color(&pyramide->color, fd);
	put_material(fd, pyramide);
	write(fd, "\t\t}\n\t", 5);
}

void		put_object_file(t_env *e, int fd)
{
	t_object	tmp;
	t_light		tmp_l;

	tmp = *e->object;
	tmp_l = *e->light;
	put_cam_win_file(e, fd);
	while (1)
	{
		put_obj_loop(fd, &tmp);
		if (tmp.next == NULL)
			break ;
		tmp = *tmp.next;
	}
	while (1)
	{
		if (!ft_strcmp("light", tmp_l.type))
			put_light_file(&tmp_l, fd);
		if (tmp_l.next == NULL)
			break ;
		tmp_l = *tmp_l.next;
	}
}

void		save_scene(t_env *e)
{
	int	fd;

	e->s_name = get_time_to_str(0);
	mkdir("./scenes/sceneshot/", 0777);
	if (!(fd = open(e->s_name, O_CREAT | O_TRUNC | O_WRONLY, 0666)))
		ft_kill("something is went wrong when saving scene");
	write(fd, "{\n\t", 3);
	put_object_file(e, fd);
	write(fd, "}\n", 2);
	close(fd);
	ft_printf("Savescene has been saved on path : %s\n", e->s_name);
	free(e->s_name);
	return ;
}
