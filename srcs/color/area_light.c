/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:18:29 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 15:18:31 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_area_size(t_object *al_object, t_light *al_light)
{
	t_vector	ray_range_max;
	t_vector	half_length;
	t_vector	half_width;

	al_light->length = v_v_subs(&al_light->point_2, &al_light->point);
	al_light->length_div = v_double_div(&al_light->length, 14);
	al_light->width = v_v_subs(&al_light->point_4, &al_light->point);
	al_light->width_div = v_double_div(&al_light->width, 14);
	half_length = v_double_div(&al_light->length, 2);
	half_width = v_double_div(&al_light->width, 2);
	al_object->center = v_v_add(&al_object->point, &half_length);
	al_object->center = v_v_add(&al_object->center, &half_width);
	ray_range_max = v_v_subs(&al_object->center, &al_object->point);
	al_object->range_max = magnitude(&ray_range_max);
}

void		get_area_light_origin(t_light *area_light, int nb)
{
	if (nb == 0)
		area_light->origin = area_light->point;
	else if (nb % 15 == 0)
	{
		area_light->origin = v_v_subs(&area_light->origin,
			&area_light->length);
		area_light->origin = v_v_add(&area_light->origin,
			&area_light->width_div);
	}
	else
		area_light->origin = v_v_add(&area_light->origin,
			&area_light->length_div);
}

t_color		get_area_light_intensity(t_env *e,
			t_light *area_light, t_rayon *ray, t_color *c)
{
	t_color		*a_c;
	t_poly		p;

	if (!(a_c = (t_color*)ft_memalloc(sizeof(t_color) * 225)))
		exit_rt(1);
	p.nb = 0;
	p.i = -1;
	while (++p.i < 225)
	{
		get_area_light_origin(area_light, p.nb);
		a_c[p.nb] = add_diffuse(e, c, area_light, ray);
		p.nb++;
	}
	p.i = -1;
	while (++p.i < 225)
	{
		c->r += a_c[p.i].r;
		c->g += a_c[p.i].g;
		c->b += a_c[p.i].b;
	}
	*c = c_double_div(c, 225);
	free(a_c);
	return (*c);
}

t_color		get_area_color(t_env *e)
{
	t_object	*area_light;
	t_vector	ray_current_range;
	double		current_range;
	double		indice;
	t_color		c;

	area_light = e->object;
	while (area_light->id != e->id_object)
		area_light = area_light->next;
	ray_current_range = v_v_subs(&area_light->center, &e->current_node);
	current_range = magnitude(&ray_current_range);
	indice = 1 - (current_range / area_light->range_max * 0.6);
	indice *= 1.6;
	indice = (indice > 1) ? 1 : indice;
	indice = (indice < 0.5) ? 0.5 : indice;
	c = set_color(1, 1, 1);
	return (c_double_mult(&c, indice));
}
