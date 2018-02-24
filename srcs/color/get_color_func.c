/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:34:35 by notraore          #+#    #+#             */
/*   Updated: 2018/02/20 11:34:38 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		color_calculation(t_env *e, t_rayon ray)
{
	t_color new;

	(void)ray;
	new = c_double_mult(&e->current_color, e->ambient);
	new = c_double_mult(&new, 1 - (e->distance / 50000));
	new = ray.refract ? c_double_mult(&new, ray.absorbtion) : new;
	return (new);
}

void		reset_diffuse_ambiant(t_env *e)
{
	e->ambient = 0;
	e->diffuse = 1;
}

t_rayon		init_ray(t_env *e)
{
	t_rayon ray;

	ray.origin = e->current_origin;
	ray.rayon = e->current_rayon;
	ray.node = e->current_node;
	ray.normal = e->current_node_normal;
	ray.refract = e->refract;
	ray.absorbtion = e->absorbtion;
	return (ray);
}
