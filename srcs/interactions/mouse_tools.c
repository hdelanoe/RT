/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 19:01:21 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/23 19:01:22 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_obj_to_add(t_object **copy)
{
	if (!ft_strcmp((*copy)->type, "cylinder"))
		create_cap_cylinder((*copy));
	else if (!ft_strcmp((*copy)->type, "cone"))
		create_cap_cone((*copy));
	else if (!ft_strcmp((*copy)->type, "glass"))
		create_child_glass((*copy));
	else if (!ft_strcmp((*copy)->type, "sphere") && (*copy)->cap)
		create_cap_sphere((*copy));
	else if (!ft_strcmp("cb", (*copy)->type))
		create_cap_cube((*copy));
	else if (!ft_strcmp("pyramide", (*copy)->type))
		create_child_pyramide((*copy));

}

int		set_lookat(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	if (cast_ray(e, e->camera.rayon, e->camera.origin))
	{
		e->lookat = e->current_node;
		return (1);
	}
	return (0);
}

int		obj_lst_size(t_object **lst)
{
	int			i;
	t_object	*tmp;

	tmp = (*lst);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	copy_cplx(t_object *copy, t_vector center)
{
	t_vector	tmp1;
	t_vector	tmp2;
	t_vector	tmp3;

	tmp1 = v_v_subs(&copy->point_2, &copy->point);
	tmp2 = v_v_subs(&copy->point_3, &copy->point);
	tmp3 = v_v_subs(&copy->point_4, &copy->point);

	copy->point = center;
	copy->point_2 = v_v_add(&copy->point, &tmp1);
	copy->point_3 = v_v_add(&copy->point, &tmp2);
	copy->point_4 = v_v_add(&copy->point, &tmp3);

}
