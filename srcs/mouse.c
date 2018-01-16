/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 19:19:34 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/05/28 20:09:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void add_object(t_env *e, int x, int y)
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
	e->copy->center = viewplane_point;
	add_new_object(&e->object, e->copy);
	ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
	if (e->aa_flag == 1 && e->pixelize == 0)
		ft_pthread(e, aa_tracer_void);
	else if (e->pixelize == 1)
		pxl_tracer(e, 13);
	else
		ft_pthread(e, ray_tracer_void);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr,
	0, 0);
}

int copy_object(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	e->is_copy = 1;
	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	if (cast_ray(e, e->camera.rayon, e->camera.origin))
		return (1);
	return (0);
}

int		mouse(int button, int x, int y, t_env *e)
{
	if (!e->copy->type && (button == 1 || button == 5))
	{
		A
		if (copy_object(e, x, y))
			ft_printf("copy %s\n", e->copy->type);
	}
	else if (e->copy->type && (button == 1 || button == 5))
	{
		A
		add_object(e, x, y);
	}
	e->is_copy = 0;
	return (0);
}
