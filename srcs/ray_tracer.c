/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:47 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	cast_ray(t_env *e, t_vector rayon, t_vector origin)
{
	t_physics	pl;
	t_camera	reflect;
	t_node		node;
	t_object 	*tmp_object;
	t_color c = set_color(0, 0, 0);
	e->current_rayon = rayon;
	e->current_origin = origin;
	e->reflect = 0;
	e->refract = 0;
//	printf("r %f g %f b %f\n", e->color_finale.r, e->color_finale.g, e->color_finale.b);
	e->color_finale = set_color(0, 0, 0);
	e->intersect = 0;
	tmp_object = e->object;
	check_intersection(e, tmp_object);
	if (e->intersect)
	{
		node.node = e->current_node;
		node.normal = e->current_node_normal;
		e->color_finale = get_color(e);
		c = e->color_finale;
	
		 if (e->reflect == 1)
		 {
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
			e->color_finale = c_c_add(&c, &reflect_color);
		}
		// if (e->refract == 1)
		// {
		// 	if (e->in_out > 0)
		// 		pl.ior = R_AIR / R_GLASS;
		// 	else
		// 		pl.ior = R_GLASS / R_AIR;
		// 	t_vector inv = v_double_mult(&rayon, (double)-1);
		//  	pl.cos1 = dot_product(&node.normal, &inv);
		//  	pl.cos2 = sqrt(1 - (pl.ior * pl.ior) * (1 - (pl.cos1 * pl.cos1)));

		//  	if (pl.cos1 >= 0)
		//  		pl.teta = pl.ior * pl.cos1 - pl.cos2;
		//  	else
		//  		pl.teta = pl.ior * pl.cos1 + pl.cos2;

		//  	pl.tmp1 = v_double_mult(&node.normal, pl.teta);
		//  	pl.tmp2 = v_double_mult(&rayon, pl.ior);
		//  	e->current_rayon = v_v_add(&pl.tmp2, &pl.tmp1);

		// 	pl.tmp1 = v_double_mult(&rayon, 0.1);
		// 	e->current_origin = v_v_add(&node.node, &pl.tmp1);

		// 	t_color lol = cast_ray(e, e->current_rayon, e->current_origin);
		// 	e->color_finale = lol;
		// 	// d->refract_color = d->color_finale;

		// 	// d->refract_color = c_c_add(&d->refract_color, &c);
		// 	// c = c_c_add(&c, &d->color_finale);
		
		// 	// 	print_color(&d->color_finale, mlx, x, y);
		// 	// exit(1);

		// }
	//	printf("r %f g %f b %f\n", d->refract_color.r, d->refract_color.g, d->refract_color.b);
	}
	return (e->color_finale);
}

void	ray_tracer(t_env *e, t_mlx *mlx)
{
	t_grid		grid;
	t_vector	viewplan_point;

	e->in_out = -1;
	e->camera.origin = set_vector(1, 1, -(double)WIN_Y);

	grid.y = 0;
	grid.y1 = (double)WIN_Y / 2;
	while (grid.y < WIN_Y)
	{
		grid.x = 0;
		grid.x1 = -(double)WIN_X / 2;
		while (grid.x < WIN_X)
		{
			e->distance = 100000;
			viewplan_point = set_vector(grid.x1, grid.y1, 0);
			e->camera.rayon = v_v_subs(&viewplan_point, &e->camera.origin);
			e->camera.rayon = normalize(&e->camera.rayon);
			cast_ray(e, e->camera.rayon, e->camera.origin);
 			print_color(&e->color_finale, mlx, grid.x, grid.y);
			grid.x++;
			grid.x1++;
		}
		grid.y++;
		grid.y1--;
	}
}


