/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:56:50 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void		*ray_tracer_void(void *e)
{
	ray_tracer(e);
	return ((void *)(1));
}

void	ray_tracer(t_env *e)
{
	static int			x;
	static int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;

	y = 0;
//	 pthread_mutex_lock(&mutex1);
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			e->in_out = -1;
			color = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = e->am_flag == 1 ? ambient_occlusion(e) :get_color(e);
			print_color(&color, e, x, y);
			x++;
		}
		y++;
	}
	// pthread_mutex_unlock(&mutex1);
}
