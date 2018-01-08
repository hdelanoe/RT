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

void	check_color(t_light *tmp_light, t_vector view_rayon, t_wave *wave, t_env *e)
{
	t_vector	tmp_angle;

	if (check_if_light_is_blocked(e))
		wave->add = set_color(0, 0, 0);
	else
	{
		tmp_angle = v_double_mult(&tmp_light->rayon, (-1));
		tmp_light->angle = dot_product(&e->current_node_normal, &tmp_angle);
		wave->specular = e->specular * get_specular(tmp_light, &view_rayon, &e->current_node_normal);
		if (tmp_light->angle <= 0)
			wave->add = set_color(0, 0, 0);
		else
		{
		//	printf("c r %f g %f b%f\n",tmp_light->color.r, tmp_light->color.g, tmp_light->color.b);
			wave->diffuse = c_c_mult(&wave->issued, &tmp_light->color);
			wave->diffuse = c_double_pow(&wave->diffuse, 1/2.2);
			wave->diffuse = c_double_add(&wave->diffuse, wave->specular);
			wave->add = c_double_mult(&wave->diffuse, tmp_light->angle);
		}
	}	
}

t_color	get_color(t_env *e)
{
	t_light		*tmp_light;
	t_vector 	view_rayon;
	t_wave 		wave;

	wave.issued = c_double_mult(&e->current_color, e->diffuse);
	wave.issued = c_double_pow(&wave.issued, 2.2);
	view_rayon = e->current_rayon;
	tmp_light = e->light;
	while (tmp_light)
	{
		tmp_light->rayon = v_v_subs(&e->current_node, &tmp_light->origin);
		e->distance_light_object = magnitude(&tmp_light->rayon);
		tmp_light->rayon = normalize(&tmp_light->rayon);
		e->current_origin = tmp_light->origin;
		e->current_rayon = tmp_light->rayon;
		check_color(tmp_light, view_rayon, &wave, e);
		e->color_finale = c_c_add(&e->color_finale, &wave.add);
		tmp_light = tmp_light->next;
	}
	e->color_finale = c_double_add(&e->color_finale, e->ambient);
	return (e->color_finale);
}