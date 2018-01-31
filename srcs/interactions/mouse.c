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

#include "../includes/rtv1.h"



int set_lookat(t_env *e, int x, int y)
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
	//	if (!((*copy) = (t_object*)ft_memalloc(sizeof(t_object))))
	//		ft_kill("Error in malloc object");
	//	init_copy(copy, e->copy);
		e->lookat = e->current_node;
		return (1);
	}
	return (0);
}

int		mouse(int button, int x, int y, t_env *e)
{
//	static t_object *copy;
	if (x > 0 && x < WIN_X && y > 0 && y < WIN_Y) // Sans cette protection, si on clique sur la le mot "RT" au dessus, ca segfault
	{
		if (!e->edit_flag)
			return (0);
		if (e->stereo_flag && (button == 1 || button == 5))
		{
			if (set_lookat(e, x, y))
			{
				ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
				camera_transformation(e);
				reset_stereo(e);
				mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 250,
					0xFFFFFF, "POV set!");
				e->flag.lookat = 1;
			//	e->stereo_flag = 0;
			//	stereo_tracer(e);
			//	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
			}
		}
		else if (!e->is_past && (button == 1 || button == 5))
		{
			if (copy_object(e, x, y))
			{
				mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 250,
					0xFFFFFF, e->copy->type);
				mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 100, 250,
					0xFFFFFF, "copied!");
				e->is_past = 1;
				// e->tmp_rad = e->copy->radius;
			}
		}
		else if (e->is_past && (button == 1 || button == 5))
		{

		//	e->tmp_rad = e->tmp_rad < 5 ? 5 : e->tmp_rad;
			// e->tmp_clr = e->copy->color;
			add_object(e, x, y);
		//	free(copy->type);
		//	ft_bzero(copy, sizeof(t_object*));
			e->is_past = 0;
		}
		else if (button == 2 || button == 6)
		{

			delete_object(e, x, y);
		//	e->tmp_rad = e->tmp_rad < 5 ? 5 : e->tmp_rad;
			// e->tmp_clr = e->copy->color;
		//	free(copy->type);
		//	ft_bzero(copy, sizeof(t_object*));
			e->is_past = 0;
		}
	}
	return (0);
}
