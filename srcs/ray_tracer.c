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

void	stereo_tracer(t_env *e)
{
	int			x;
	int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;
	t_color		sred;
	t_color 	sblue;
	t_color		red;
	t_color 	blue;
	
	y = 0;

	red = set_color(0, 0, 1);
	blue = set_color(1, 1, 0);
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			e->recursion = 6;
			sblue = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->lstereo.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->lstereo.y_vector, y);
			viewplane_point = v_v_add(&e->lviewplane, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->lstereo.rayon = v_v_subs(&viewplane_point, &e->lstereo.origin);
			e->lstereo.rayon = normalize(&e->lstereo.rayon);
			if (cast_ray(e, e->lstereo.rayon, e->lstereo.origin))
			{
				sblue = e->am_flag == 1 ? ambient_occlusion(e) :get_color(e);
				sblue = c_c_add(&sblue, &blue);
			}
			sred = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->rstereo.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->rstereo.y_vector, y);
			viewplane_point = v_v_add(&e->rviewplane, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->rstereo.rayon = v_v_subs(&viewplane_point, &e->rstereo.origin);
			e->rstereo.rayon = normalize(&e->rstereo.rayon);
			if (cast_ray(e, e->rstereo.rayon, e->rstereo.origin))
			{
				sred = e->am_flag == 1 ? ambient_occlusion(e) :get_color(e);
				sred = c_c_add(&sred, &red);
			}
			color = c_c_mult(&sblue, &sred);
			print_color(&color, e, x, y);
			x++;
		}
		y++;
	}
}

void	edit_tracer(t_env *e)
{
	static int			x;
	static int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;
	
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			e->recursion = 6;
			color = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = e->current_color;
				print_color(&color, e, x, y);
			x++;
		}
		y++;
	}
}

void	ray_tracer(t_env *e)
{
	int			x;
	int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_color 	color;
	
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			e->recursion = 6;
			color = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				color = e->am_flag == 1 ? ambient_occlusion(e) : get_color(e);
			if (color.r != 0 || color.g != 0 || color.b != 0)
				print_color(&color, e, x, y);
			x++;
		}
		y++;
	}
}
