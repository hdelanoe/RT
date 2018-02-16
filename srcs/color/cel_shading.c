/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/05 15:25:38 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		cel_shading(t_vector *light, t_env *e, t_color *clr)
{
	t_color		new;
	double		intens;
	t_vector	nrm;

	new = set_color(0, 0, 0);
	nrm = normalize(&e->current_node_normal);
	if (e->intersect)
		intens = -(dot_product(light, &nrm));
	else
		return (set_color(0, 0, 0));
	if (intens < 0.2)
		intens = 0.1;
	else if (intens >= 0.2 && intens < 0.6)
		intens = 0.3;
	else if (intens >= 0.6)
		intens = 0.7;
	else
		return (set_color(0, 0, 0));
	new = set_color(intens, intens, intens);
	return (c_c_add(&new, clr));
}

t_color		cel_shade_color(t_env *e)
{
	t_color		c;

	c = e->current_color;
	e->light->rayon = v_v_subs(&e->current_node, &e->light->origin);
	e->light->rayon = normalize(&e->light->rayon);
	c = cel_shading(&e->light->rayon, e, &c);
	return (c);
}
