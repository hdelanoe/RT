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

#include "rt.h"



void		area_rays_ratio(t_light *al_light,
			double *magn_length, double *magn_width)
{
	double		relation;

	relation = (*magn_length >= *magn_width) ?
	(*magn_width / *magn_length) : (*magn_length / *magn_width);
	if (relation >= 0.5)
	{
		al_light->ratio_length = 14;
		al_light->ratio_width = 14;
	}
	else if (relation >= 0.2)
	{
		al_light->ratio_length = 24;
		al_light->ratio_width = 8;
	}
	else if (relation >= 0.05)
	{
		al_light->ratio_length = 44;
		al_light->ratio_width = 4;
	}
	else
	{
		al_light->ratio_length = 74;
		al_light->ratio_width = 2;
	}
}

void		init_area_size_2(t_object *al_object, t_light *al_light)
{
	t_vector	ray_range_max;
	t_vector	half_length;
	t_vector	half_width;
	
	half_length = v_double_div(&al_light->length, 2);
	half_width = v_double_div(&al_light->width, 2);
	al_object->center = v_v_add(&al_object->point, &half_length);
	al_object->center = v_v_add(&al_object->center, &half_width);
	ray_range_max = v_v_subs(&al_object->center, &al_object->point);
	al_object->range_max = magnitude(&ray_range_max);
}

void		init_area_size(t_object *al_object, t_light *al_light)
{
	double		magn_length;
	double		magn_width;
	double		tmp;

	al_light->ratio_length = 0;
	al_light->ratio_width = 0;
	al_light->length = v_v_subs(&al_light->point_2, &al_light->point);
	al_light->width = v_v_subs(&al_light->point_4, &al_light->point);
	magn_length = magnitude(&al_light->length);
	magn_width = magnitude(&al_light->width);
	area_rays_ratio(al_light, &magn_length, &magn_width);
	if (magn_length < magn_width)
	{
		tmp = al_light->ratio_width;
		al_light->ratio_width = al_light->ratio_length;
		al_light->ratio_length = tmp;
	}
	al_light->length_div = v_double_div(&al_light->length,
		al_light->ratio_length);
	al_light->width_div = v_double_div(&al_light->width,
		al_light->ratio_width);
	init_area_size_2(al_object, al_light);
}

void		get_area_light_origin(t_light *area_light, int nb)
{
	if (nb == 0)
		area_light->origin = area_light->point;
	else if (nb % ((int)area_light->ratio_length + 1) == 0)
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
