/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:33:30 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/23 16:52:43 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		plane_intersection(t_env *e, t_object *plane)
{
	double		a;
	double		b;
	double		s;
	t_vector	plan_cam;
	t_vector	tmp_node;

	plan_cam = v_v_subs(&e->current_origin, &plane->point);
	a = dot_product(&plane->normal, &e->current_rayon);
	b = dot_product(&plane->normal, &plan_cam);
	s = -(b / a);
	e->solution = s;
	if (e->solution < 0 || s < 0 || a == 0)
		return (0);
	tmp_node = v_double_mult(&e->current_rayon, e->solution);
	plane->node = v_v_add(&e->current_origin, &tmp_node);
	if (a < 0)
		plane->node_normal = plane->normal;
	else
		plane->node_normal = v_double_mult(&plane->normal, (-1));
	return (1);
}

int		sphere_intersection(t_env *e, t_object *sphere)
{
	t_poly 	p;
	t_inter i;

	i.object_rayon = v_v_subs(&e->current_origin, &sphere->center);
	p.b = dot_product(&i.object_rayon, &e->current_rayon);
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (sphere->radius * sphere->radius);
	p.discriminant = (p.b * p.b) - p.c;
	if (p.discriminant < 0)
		return (0);
	if (p.discriminant == 0)
		e->solution = - p.b;
	else
	{
		p.discriminant = sqrt(p.discriminant);
		p.s1 = (- p.b + p.discriminant);
		p.s2 = (- p.b - p.discriminant);
		e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
	}
	if (e->solution < 0)
		return (0);
	i.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	sphere->node = v_v_add(&e->current_origin, &i.tmp_node);
	sphere->node_normal = v_v_subs(&sphere->node, &sphere->center);
	sphere->node_normal = normalize(&sphere->node_normal);
	return (1);
}

int		cylinder_intersection(t_env *e, t_object *cylinder)
{
	t_poly	p;
	t_inter	i;

	i.object_rayon = v_v_subs(&e->current_origin, &cylinder->center);
	p.a = 1 - (dot_product(&e->current_rayon, &cylinder->axis) * dot_product(&e->current_rayon, &cylinder->axis));
	p.b = 2 * (dot_product(&i.object_rayon, &e->current_rayon) - (dot_product(&e->current_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)));
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (dot_product(&i.object_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)) - (cylinder->radius * cylinder->radius);
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
//	poly_2nd_degree(d, &p, &i, cylinder);
	if (p.discriminant < 0)
		return (0);
	if (p.discriminant == 0)
		e->solution = - (p.b / (2 * p.a));
	else
	{
		p.discriminant = sqrt(p.discriminant);
		p.s1 = (- p.b + p.discriminant) / (2 * p.a);
		p.s2 = (- p.b - p.discriminant) / (2 * p.a);
		e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
		if (p.s1 > p.s2) // FT_SWAP
        {
            double tmp;
            tmp = p.s1;
            p.s1 = p.s2;
            p.s2 = tmp;
            e->solution = p.s1;
        }
	}
	if (e->solution < 0)
		return (0);
	i.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	cylinder->node = v_v_add(&e->current_origin, &i.tmp_node);
	p.tmp1 = (dot_product(&e->current_rayon, &cylinder->axis) * e->solution) + dot_product(&i.object_rayon, &cylinder->axis);
	p.tmp2 = (dot_product(&e->current_rayon, &cylinder->axis) * p.s2) + dot_product(&i.object_rayon, &cylinder->axis);
	if (p.tmp1 > cylinder->lenght_max || p.tmp1 < 0)
		return (0);
	i.tmp_node_normal1 = v_v_subs(&cylinder->node, &cylinder->center);
	i.tmp_node_normal2 = v_double_mult(&cylinder->axis, p.tmp1);
	cylinder->node_normal = v_v_subs(&i.tmp_node_normal1, &i.tmp_node_normal2);
	cylinder->node_normal = normalize(&cylinder->node_normal);
	return (1);
}

int disk_intersection(t_env *e, t_object *disk)
{
    if(plane_intersection(e, disk))
    {
        t_vector distance = v_v_subs(&disk->node, &disk->point);
        double d = dot_product(&distance, &distance);
        if (d <= (disk->radius * disk->radius))
            return (1);
    }
    return (0);
}

int		cone_intersection(t_env *e, t_object *cone)
{
	t_poly 	p;
	t_inter i;

	i.object_rayon = v_v_subs(&e->current_origin, &cone->vertex);
	p.tmp1 = (1 + pow(cone->tangent, 2));
	p.tmp2 = dot_product(&e->current_rayon, &cone->axis);
	p.tmp3 = dot_product(&i.object_rayon, &cone->axis);

	p.a = 1 - (p.tmp1 * pow(p.tmp2, 2));
	p.b = 2 * ((dot_product(&i.object_rayon, &e->current_rayon) - (p.tmp1 * (p.tmp2 * p.tmp3))));
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (p.tmp1 * (p.tmp3 * p.tmp3));
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	if (p.discriminant < 0)
		return (0);
	if (p.discriminant == 0)
		e->solution = - (p.b / (2 * p.a));
	else
	{
		p.discriminant = sqrt(p.discriminant);
		p.s1 = (- p.b + p.discriminant) / (2 * p.a);
		p.s2 = (- p.b - p.discriminant) / (2 * p.a);
		e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
	}
	if (e->solution < 0)
		return (0);
	i.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	cone->node = v_v_add(&e->current_origin, &i.tmp_node);

	p.len = (p.tmp2 * e->solution) + p.tmp3;
	if (p.len > cone->lenght_max || p.len < 0)
		return (0);
	i.tmp_node_normal1 = v_v_subs(&cone->node, &cone->vertex);
	i.tmp_node_normal2 = v_double_mult(&cone->axis, p.len);
	i.tmp_node_normal2 = v_double_mult(&i.tmp_node_normal2, p.tmp1);
	cone->node_normal = v_v_subs(&i.tmp_node_normal1, &i.tmp_node_normal2);
	cone->node_normal = normalize(&cone->node_normal);
	return (1);
}