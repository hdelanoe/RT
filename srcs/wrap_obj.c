/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2018/02/26 20:20:04 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		wrap_sphere(t_env *e, t_object *object)
{
	t_vector			vp;
	double				phi;
	t_vector			vecdirx;
	t_vector			vecdiry;
	t_vector			cross;

	vecdirx = (t_vector){1, 0, 0};
	vecdiry = (t_vector){0, 1, 0};
	cross = v_v_mult(&vecdiry, &vecdirx);
	vp = v_v_subs(&object->center, &e->current_node);
	vp = normalize(&vp);
	phi = acos(-dot_product(&vecdiry, &vp));
	e->v = phi / PI;
	e->u = (acos(-dot_product(&vp, &vecdirx) / sin(phi))) / (2.0 * PI);
	if (!(dot_product(&cross, &vp) > 0.0))
		e->u = 1.0 - e->u;
	e->i = !ft_strcmp(object->type, "plane") || object->skybox
	? (int)(e->v * (e->bpp[e->ti]))
	: (int)(e->v * (e->bpp[e->ti] - e->strechx));
	e->j = object->skybox || !ft_strcmp(object->type, "plane") ?
	(int)(e->u * e->sl[e->ti]) : (int)(e->u * e->sl[e->ti] + e->pet);
	e->current_color = get_texture_info(e->tx_dta[e->ti],
	e, e->sl[e->ti]);
	return (e->current_color);
}

t_color		wrap_plane(t_env *e, t_object *object)
{
	double					x;
	double					y;
	double					xx;
	double					yy;

	x = fabs(object->point.x - object->point_2.x);
	y = fabs(object->point.y - object->point_3.y);
	xx = fabs(object->point.x - object->node.x);
	if (fabs(object->node_normal.z) < fabs(object->node_normal.y))
		yy = fabs(object->point.z - object->node.z);
	else
		yy = fabs(object->point.y - object->node.y);
	e->i = (int)(yy * (e->bpp[e->ti]) / y);
	e->j = (int)(xx * (e->sl[e->ti]) / x);
	return (get_texture_info(e->tx_dta[e->ti],
	e, e->sl[e->ti]));
}

t_color		wrap_cylinder(t_env *e, t_object *object)
{
	t_vector sub;

	sub = v_v_subs(&object->center, &e->current_node);
	sub = normalize(&sub);
	e->u = sub.y * 0.5 + 0.5;
	e->v = -atan2(sub.x, sub.z) / (2 * PI) + 0.5;
	e->i = (int)(e->u * (e->bpp[e->ti] - e->strechx));
	e->j = (int)(e->v * e->sl[e->ti] + (e->pet % e->sl[e->ti]));
	return (get_texture_info(e->tx_dta[e->ti], e,
	e->sl[e->ti]));
}

t_color		wrap_cone(t_env *e, t_object *object)
{
	t_vector	sub;
	t_vector	tmp;
	t_vector	tmp_2;

	tmp_2 = v_double_mult(&object->axis, (object->lenght_max) / 2);
	tmp = v_v_add(&object->center, &tmp_2);
	sub = v_v_subs(&tmp, &e->current_node);
	sub = normalize(&sub);
	e->u = sub.y * 0.5 + 0.5;
	e->v = -atan2(sub.x, sub.z) / (2 * PI) + 0.5;
	e->i = (int)(e->u * (e->bpp[e->ti] - e->strechx));
	e->j = (int)(e->v * e->sl[e->ti] + e->pet);
	return (get_texture_info(e->tx_dta[e->ti], e,
	e->sl[e->ti]));
}
