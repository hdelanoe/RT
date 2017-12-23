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

void 	init_rayon_values(t_env *e, t_vector rayon, t_vector origin)
{
	e->current_rayon = rayon;
	e->current_origin = origin;
	e->color_finale = e->refract_color;
	e->intersect = 0;
	e->reflect = 0;
	e->refract = 0;
	e->bump = 0;
}

t_vector bump_normal(t_vector normal)
{
	double n;

	n = noise(normal.x, normal.y, normal.z);
	return (v_double_mult(&normal, n));
}

t_color	cast_ray(t_env *e, t_vector rayon, t_vector origin)
{
	t_physics	pl;
	t_camera	reflect;
	t_camera 	refract;
	t_node		node;
	t_object 	*tmp_object;
	t_color 	c;

	c = set_color(0, 0, 0);
	init_rayon_values(e, rayon, origin);
//	printf("r %f g %f b %f\n", e->color_finale.r, e->color_finale.g, e->color_finale.b);
	tmp_object = e->object;
	check_intersection(e, tmp_object);
	if (e->intersect)
	{

		node.node = e->current_node;
		node.normal = e->current_node_normal;
		if (e->bump)
		{
			node.node = bump_normal(e->current_node);
			node.normal = bump_normal(e->current_node_normal);
		}
		e->color_finale = get_color(e);
		if (e->reflect == 1)
		{
			c = e->color_finale;
			t_vector inv = v_double_mult(&rayon, (double)-1);
			pl.cos1 = dot_product(&inv, &node.normal);
			if (pl.cos1 >= 0)
				pl.teta = 2 * pl.cos1;
			else
				pl.teta = -2 * pl.cos1;
			pl.tmp1 = v_double_mult(&node.normal, pl.teta);
			reflect.rayon = v_v_add(&rayon, &pl.tmp1);

			pl.tmp1 = v_double_mult(&reflect.rayon, 0.01);
			reflect.origin = v_v_add(&node.node, &pl.tmp1);

			t_color reflect_color = cast_ray(e, reflect.rayon, reflect.origin);
			reflect_color = c_double_mult(&reflect_color, 0.50);
			c = c_double_mult(&c, 0.50);
			e->color_finale = c_c_add(&c, &reflect_color);
		}
		if (e->refract == 1)
		{
			e->in_out *= -1;
			c = e->color_finale;
		 	if (e->in_out > 0)
		 		pl.ior = R_VOID / R_AIR;
		 	else
		 		pl.ior = R_AIR / R_VOID;
		 	t_vector inv = v_double_mult(&rayon, -1.0);
		 	pl.cos1 = dot_product(&node.normal, &inv);
		 	pl.cos2 = sqrt(1 - (pl.ior * pl.ior) * (1 - (pl.cos1 * pl.cos1)));
   			// if (pl.cos1 >= 0) 
      //   	 	pl.teta = pl.ior * pl.cos1 - pl.cos2; 
      //  		else 
         		pl.teta = pl.ior * pl.cos1 + pl.cos2; 
		 	pl.tmp1 = v_double_mult(&node.normal, pl.teta);
		 	pl.tmp2 = v_double_mult(&rayon, pl.ior);
		 	refract.rayon = v_v_add(&pl.tmp2, &pl.tmp1);

		 	pl.tmp1 = v_double_mult(&refract.rayon, 0.01);
		 	refract.origin = v_v_add(&node.node, &pl.tmp1);
		 	e->refract_color = c_double_mult(&c, 1 - e->absorbtion);

		 	t_color lol = cast_ray(e, refract.rayon, refract.origin);
		 	t_color xd2 = c_double_mult(&lol, e->absorbtion);
		 	e->color_finale = c_c_add(&e->refract_color, &xd2);
		}
	}
	return (e->color_finale);
}

void	ray_tracer(t_env *e)
{
	int			x;
	int			y;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	e->in_out = -1;
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			e->refract_color = set_color(0, 0, 0);
			e->distance = 100000;
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			cast_ray(e, e->camera.rayon, e->camera.origin);
 			print_color(&e->color_finale, e, x, y);
			x++;
		}
		y++;
	}
}

// while (y < HEIGHT)
// 	{
// 		x = 0;
// 		x1 = -(WIDTH / 2);
// 		while (x < WIDTH)
// 		{
// 			all->dist = 200000;
// 			all->ray = init_ray(all, x1, y1);
// 			tmpy = all->y;
// 			tmpx = x;
// 			while (all->y < tmpy + pxlnbr)
// 			{
// 				if (x != tmpx)
// 				{
// 					x -= pxlnbr;
// 					x1 -= pxlnbr;
// 				}
// 				while (x < tmpx + pxlnbr)
// 				{
// 					if (x > 0 && x < WIDTH && all->y < HEIGHT && all->y > 0)
// 						pixel_puts(&all->clr, all);
// 					x++;
// 					x1++;
// 				}
// 				all->y++;
// 			}
// 			all->y = tmpy;
// 			all->o_tmp = all->head;
// 		}
// 		all->y += pxlnbr;
// 		y1 -= pxlnbr;
// 	}

void	pxl_tracer(t_env *e)
{
	int			x;
	int			y;

	int			tmpx;
	int			tmpy;
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	e->in_out = -1;
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			tmpx = x;
			tmpy = y;
			e->refract_color = set_color(0, 0, 0);
			e->distance = 100000;
			tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
			viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
			viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
			e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			cast_ray(e, e->camera.rayon, e->camera.origin);
			while (y < tmpy + 13)
			{
				if (x != tmpx)
					x -= 13;
				while (x < tmpx + 13)
				{
 					print_color(&e->color_finale, e, x, y);
 					x++;
 				}
 				y++;
 			}
			y = tmpy;
		}
		y+=13;
	}
}