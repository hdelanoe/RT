/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double get_specular(t_light *light, t_vector *view, t_vector *node)
{
	double 		reflect;
	t_vector      tmp;
	double 		phong_color;
	t_vector	r;

	reflect =  dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);

	phong_color = 0.2 * powf(dot_product(view, &r), 50) * 3;

	return (phong_color);
}

t_color	get_color(t_env *e)
{
	t_vector	tmp_angle;
	t_light		*tmp_light;
	t_vector 	view_rayon;
	t_color 	add;
	
	add = c_double_pow(&e->current_color, 1/2.2);
	view_rayon = e->current_rayon;
	tmp_light = e->light;
	while (tmp_light)
	{
		tmp_light->rayon = v_v_subs(&e->current_node, &tmp_light->origin);
		e->distance_light_object = magnitude(&tmp_light->rayon);
		tmp_light->rayon = normalize(&tmp_light->rayon);
		e->current_origin = tmp_light->origin;
		e->current_rayon = tmp_light->rayon;

		if (check_if_light_is_blocked(e))
			add = set_color(0, 0, 0); 
		else
		{
			tmp_angle = v_double_mult(&tmp_light->rayon, (-1));
			tmp_light->angle = dot_product(&e->current_node_normal, &tmp_angle);
			if (tmp_light->angle <= 0)
				add = set_color(0, 0, 0);
			else
			{
				add = c_c_mult(&add, &tmp_light->color);
				add = c_double_pow(&add, 1/2.2);
			 	add = c_double_add(&add, get_specular(tmp_light, &e->current_rayon, &e->current_node_normal));
			//	printf("color r %f, g %f, b %f \n", add.r, add.g, add.b);
				add = c_double_mult(&add, tmp_light->angle);
			}
		}
		e->color_finale = c_c_add(&e->color_finale, &add);
		tmp_light = tmp_light->next;
	}
	return (e->color_finale);
}