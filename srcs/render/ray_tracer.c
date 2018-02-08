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

t_color	choose_color(t_env *e)
{
	t_color new;

	if (e->aa_flag == 1 && e->pixelize == 0)
	{
		if (e->cel_shade == 1)
			new = e->current_color;
		else
			new = get_color(e);
	}
	else if (e->pixelize == 1)
	{
		if (e->edit_flag == 1)
			new = e->current_color;
		else if (e->cel_shade == 1)
			new = cel_shade_color(e);
		else
			new = get_color(e);
	}
	else if (e->edit_flag == 1)
		new = e->current_color;
	else if (e->cel_shade == 1)
		new = cel_shade_color(e);
	else
		new = get_color(e);
	return (new);
}

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
	t_color c;
	
	y = 0;

	red = set_color(0, 0, 1);
	blue = set_color(1, 1, 0);
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			c = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			if (cast_ray(e, e->camera.rayon, e->camera.origin))
				c = get_color(e);
			e->recursion = 6;
			sblue = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->lstereo.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->lstereo.y_vector, y);
			viewplane_point = v_v_add(&e->lviewplane, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->lstereo.rayon = v_v_subs(&viewplane_point, &e->lstereo.origin);
			e->lstereo.rayon = normalize(&e->lstereo.rayon);
			if (cast_ray(e, e->lstereo.rayon, e->lstereo.origin))
				sblue = get_color(e);
			if (e->render_mode != 4)
				sblue = c_c_add(&sblue, &blue);
			e->recursion = 6;
			sred = set_color(0, 0, 0);
			tmp_vp_pointx = v_double_mult(&e->rstereo.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->rstereo.y_vector, y);
			viewplane_point = v_v_add(&e->rviewplane, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->rstereo.rayon = v_v_subs(&viewplane_point, &e->rstereo.origin);
			e->rstereo.rayon = normalize(&e->rstereo.rayon);
			if (cast_ray(e, e->rstereo.rayon, e->rstereo.origin))
				sred = get_color(e);
			if (e->render_mode != 4)
				sred = c_c_add(&sred, &red);
			if (e->render_mode == 2)
				color = c_c_mult(&sblue, &sred);
			else
			{
				e->recursion = 6;
				c = set_color(0, 0, 0);
				tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
				tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
				viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
				viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
				e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
				e->camera.rayon = normalize(&e->camera.rayon);
				if (cast_ray(e, e->camera.rayon, e->camera.origin))
					c = get_color(e);
				color.r = sblue.r +  sred.r + c.r;
				color.g = sblue.g +  sred.g + c.g;
				color.b = sblue.b +  sred.b + c.b;
				color = c_double_mult(&color, 0.3);
			}
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
			{
				if (e->render_mode == 1 && !e->edit_flag)
					color = ambient_occlusion(e);
				else if (e->render_mode == 3 && !e->edit_flag)
					color = cel_shade_color(e);
				else if (e->area_light_on == 1)
					color = get_area_color(e);
				else
					color = get_color(e);
			}
			color = set_filter(e, color);
		//	if (color.r != 0 || color.g != 0 || color.b != 0)
				print_color(&color, e, x, y);
			e->skybox = 0;
			x++;
		}
		y++;
	}
}
