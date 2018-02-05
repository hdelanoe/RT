/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:17:11 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 15:22:46 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shoot_new_color(t_env *e, t_color *c, double coef)
{
	t_color shade;
	t_color shade_sub;

	shade = get_color(e);
	shade_sub = set_color(0.5, 0.5, 0.5);
	shade = c_double_mult(&shade, coef);
	if (shade.r < 0.1 && shade.g < 0.1 && shade.b < 0.1)
		*c = c_c_subs(c, &shade_sub);
	else
		*c = c_c_add(c, &shade);
}

void		recurse_color(t_env *e, t_rayon ray, t_color *c)
{
	while (--(e->recursion) > 0)
	{
		if (e->reflect)
		{
			if (cast_reflect_ray(e, ray))
				shoot_new_color(e, c, e->diffuse);
		}
		else if (e->refract)
		{
			if (cast_refract_ray(e, ray))
				shoot_new_color(e, c, 1 - e->absorbtion);
		}
	}
}
