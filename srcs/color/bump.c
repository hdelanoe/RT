/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:27:12 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/26 13:27:13 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		bump_water(t_env *e, t_rayon *ray)
{
	double n;

	n = noise(e, e->perlin.a * ray->node.x,
	e->perlin.c * ray->node.y, e->perlin.b * ray->node.z);
	ray->node.y *= n;
	ray->normal = v_double_add(&ray->normal, n);
	ray->normal = normalize(&ray->normal);
}

void		bump_marble(t_env *e, t_color *c, t_rayon *ray)
{
	double n;

	n = 1 - sqrt(fabs(sin(2 * 3.1416 * noise(e, e->perlin.a * ray->node.x,
		e->perlin.c * ray->node.y, e->perlin.b * ray->node.z))));
	c->r *= 1.0 * (1 - n) + 0.7 * n;
	c->g *= 1.0 * (1 - n) + 0.7 * n;
	c->b *= 1.0 * (1 - n) + 0.7 * n;
}

void		bump_wood(t_env *e, t_color *c, t_rayon *ray)
{
	double		n;
	double		value;
	t_color		tmp1;
	t_color		tmp2;

	tmp1 = set_color(0.1, 0.2, 0.5);
	tmp2 = set_color(0.02, 0.3, 0.4);
	value = fmod(noise(e, e->perlin.a * ray->node.x,
		e->perlin.c * ray->node.z, e->perlin.b * ray->node.y), 0.2);
	value = value > 0.2 / 2 ? 0.2 - value : value;
	n = (1 - cos(3.1416 * value / (0.2 / 2))) / 2;
	c->r *= (tmp1.r * (1 - n) + tmp2.r * n);
	c->g *= (tmp1.r * (1 - n) + tmp2.g * n);
	c->b *= (tmp1.b * (1 - n) + tmp2.b * n);
}

t_color		apply_bump(t_env *e, t_rayon *ray, t_color c)
{
	t_color new;
	int		carre;

	new = c;
	carre = floor(e->current_node.x) + floor(e->current_node.z);
	if (ray->bump == 2)
		bump_marble(e, &new, ray);
	else if (ray->bump == 3)
		bump_wood(e, &new, ray);
	else if (ray->bump == 4 && carre % 2 == 0)
		return ((t_color){0, 0, 0});
	return (new);
}
