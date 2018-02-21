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

#include "../includes/rtv1.h"

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
	tmp_2 = ft_strdup("\"\n");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}
