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

void		get_area_light_origin(t_env *e, t_light *area_light, int nb)
{
	if (nb == 0)
		area_light->origin = area_light->point;
	else if (nb % 4 == 0)
	{
		area_light->origin = v_v_subs(&area_light->origin, &e->rayon_length);
		area_light->origin = v_v_add(&area_light->origin, &e->rayon_width_div);
	}
	else
		area_light->origin = v_v_add(&area_light->origin, &e->rayon_length_div);
}

t_color		get_area_light_intensity(t_env *e, t_light *area_light, t_rayon *ray, t_color *c)
{
	t_color 	diffuse;
	t_color		*a_c;
	int			i;
	int			j;
	int			nb;
	double 		specular;
	t_vector 	tmp_angle;
	t_color   	c_light;

	if(!(a_c = (t_color*)ft_memalloc(sizeof(t_color) * 16)))
		exit_rt(1);
	e->rayon_length = v_v_subs(&area_light->point_2, &area_light->point);
	e->rayon_length_div = v_double_div(&e->rayon_length, 3);
	e->rayon_width = v_v_subs(&area_light->point_4, &area_light->point);
	e->rayon_width_div = v_double_div(&e->rayon_width, 3);
	nb = 0;
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			get_area_light_origin(e, area_light, nb);
			// printf("area_light->origin: %f, %f, %f\n", area_light->origin.x, area_light->origin.y, area_light->origin.z);
			diffuse = set_color(0, 0, 0);
			area_light->rayon = v_v_subs(&e->current_node, &area_light->origin);
			e->distance_light_object = magnitude(&area_light->rayon);
			area_light->rayon = normalize(&area_light->rayon);
			e->current_origin = area_light->origin;
			e->current_rayon = area_light->rayon;
			c_light = light_intersection(e, area_light);
			if (!(c_light.r == 0 && c_light.g == 0 && c_light.b == 0))
			{
				tmp_angle = v_double_mult(&area_light->rayon, (-1));
				area_light->angle = dot_product(&e->current_node_normal, &tmp_angle);
				specular = e->specular * get_specular(area_light, &ray->rayon, &ray->normal);
				if (area_light->angle > 0)
				{
					diffuse = c_c_mult(&e->current_color, &area_light->color);
					diffuse = c_double_add(&diffuse, specular);
					diffuse = c_double_mult(&diffuse, area_light->angle);
					diffuse = c_double_mult(&diffuse, e->diffuse);
				}
				a_c[nb] = c_c_add(c, &diffuse);
			}
			else
				a_c[nb] = *c;
			nb++;
			i++;
		}
		j++;
	}
	// printf("\n");
	i = 0;
	while (i < 16)
	{
		c->r += a_c[i].r;
		c->g += a_c[i].g;
		c->b += a_c[i].b;
		i++;
	}
	*c = c_double_div(c, 16);
	free(a_c);
	return (*c);
}