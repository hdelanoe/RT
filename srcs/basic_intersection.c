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
	t_poly	p;

	p.object_rayon = v_v_subs(&e->current_origin, &plane->point);
	p.a = dot_product(&plane->normal, &e->current_rayon);
	p.b = dot_product(&plane->normal, &p.object_rayon);
	p.s1 = -(p.b / p.a);
	e->solution = p.s1;
	if (e->solution < 0 || p.s1 < 0 || p.a == 0)
		return (0);
	p.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	plane->node = v_v_add(&e->current_origin, &p.tmp_node);
	if (p.a < 0)
		plane->node_normal = plane->normal;
	else
		plane->node_normal = v_double_mult(&plane->normal, (-1));
	return (1);
}

/*int 	check_demisphere(t_object *sphere, t_inter *i)
{
	t_vector distance;

	distance = v_v_subs(&i->tmp_node, &sphere->center);
	if (distance.y < 0)
		return (1);
	else
		return (0);
}*/

int		sphere_intersection(t_env *e, t_object *sphere)
{
	t_poly 	p;

	p.object_rayon = v_v_subs(&e->current_origin, &sphere->center);
	p.b = dot_product(&p.object_rayon, &e->current_rayon);
	p.c = dot_product(&p.object_rayon, &p.object_rayon) -
	(sphere->radius * sphere->radius);
	p.discriminant = (p.b * p.b) - p.c;
	return (sphere_solution(e, sphere, p));
}

int		cylinder_intersection(t_env *e, t_object *cylinder)
{
	t_poly	p;

	p.object_rayon = v_v_subs(&e->current_origin, &cylinder->center);
	p.a = 1 - (dot_product(&e->current_rayon, &cylinder->axis) *
		dot_product(&e->current_rayon, &cylinder->axis));
	p.b = 2 * (dot_product(&p.object_rayon, &e->current_rayon) -
		(dot_product(&e->current_rayon, &cylinder->axis) *
			dot_product(&p.object_rayon, &cylinder->axis)));
	p.c = dot_product(&p.object_rayon, &p.object_rayon) -
	(dot_product(&p.object_rayon, &cylinder->axis) *
		dot_product(&p.object_rayon, &cylinder->axis)) -
	(cylinder->radius * cylinder->radius);
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	return (cylinder_solution(e, cylinder, p));
}

int disk_intersection(t_env *e, t_object *disk, t_object *parent)
{
    if(plane_intersection(e, disk))
    {
        t_vector distance = v_v_subs(&disk->node, &disk->point);
        double d = dot_product(&distance, &distance);
        if (d <= (disk->radius * disk->radius))
        {
        	if (parent)
        	{
        		parent->node = disk->node;
        		parent->node_normal = disk->node_normal;
        	}
            return (1);
        }
    }
    return (0);
}

int		cone_intersection(t_env *e, t_object *cone)
{
	t_poly 	p;

	p.object_rayon = v_v_subs(&e->current_origin, &cone->vertex);
	p.tmp1 = (1 + pow(cone->tangent, 2));
	p.tmp2 = dot_product(&e->current_rayon, &cone->axis);
	p.tmp3 = dot_product(&p.object_rayon, &cone->axis);
	p.a = 1 - (p.tmp1 * pow(p.tmp2, 2));
	p.b = 2 * ((dot_product(&p.object_rayon,&e->current_rayon) -
		(p.tmp1 * (p.tmp2 * p.tmp3))));
	p.c = dot_product(&p.object_rayon, &p.object_rayon) -
	(p.tmp1 * (p.tmp3 * p.tmp3));
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	return (cone_solution(e, cone, p));
}
