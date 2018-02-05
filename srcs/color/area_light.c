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

void		init_area_size(t_light *area_light)
{
	area_light->length = v_v_subs(&area_light->point_2, &area_light->point);
	area_light->length_div = v_double_div(&area_light->length, 14);
	area_light->width = v_v_subs(&area_light->point_4, &area_light->point);
	area_light->width_div = v_double_div(&area_light->width, 14);
}

void		get_area_light_origin(t_light *area_light, int nb)
{
	if (nb == 0)
		area_light->origin = area_light->point;
	else if (nb % 15 == 0)
	{
		area_light->origin = v_v_subs(&area_light->origin, &area_light->length);
		area_light->origin = v_v_add(&area_light->origin, &area_light->width_div);
	}
	else
		area_light->origin = v_v_add(&area_light->origin, &area_light->length_div);
}

t_color		get_area_light_intensity(t_env *e, t_light *area_light, t_rayon *ray, t_color *c)
{
	t_color		*a_c;
	t_poly		p;

	if(!(a_c = (t_color*)ft_memalloc(sizeof(t_color) * 225)))
		exit_rt(1);
	p.nb = 0;
	p.i = 0;
	while (p.i++ < 225)
	{
		get_area_light_origin(area_light, p.nb);
		a_c[p.nb] = add_diffuse(e, c, area_light, ray);
		p.nb++;
	}
	p.i = 0;
	while (p.i++ < 225)
	{
		c->r += a_c[p.i].r;
		c->g += a_c[p.i].g;
		c->b += a_c[p.i].b;
	}
	*c = c_double_div(c, 225);
	free(a_c);
	return (*c);
}