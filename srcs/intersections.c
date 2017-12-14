/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/rtv1.h"
#include "rtv1.h"

// int		torus_intersection(t_datas *data, t_torus *torus)
// {
// 	double 		a;
// 	double		b;
// 	double		c;
// 	double      d;
// 	double      e;
// 	double  	m;
// 	double 		n;
// 	double 		o;
// 	double 		p;
// 	double 		q;
// 	double 		k;
// 	t_vector 		r;
// 	double 			s;
// 	double		s1;
// 	double		s2;
// 	double		discriminant;
// 	t_vector 	tmp;
// 	t_vector	torus_origin;
// 	t_vector	tmp_node;

// 	torus_origin = v_v_subs(&data->current_origin, &torus->center);

// 	m = dot_product(&data->current_rayon, &data->current_rayon);
// 	//printf("m = %f", m);
// 	n = dot_product(&data->current_rayon, &torus_origin);
// 	o = dot_product(&torus_origin, &torus_origin);
// 	p = dot_product(&data->current_rayon, &torus->axis);
// 	q = dot_product(&torus_origin, &torus->axis);
// 	a = pow(m, 2);
// 	b = (4 * m * n);
// 	c = ((4 * pow(m, 2)) + (2 * m * o) - (2 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * m) + (4 * pow(torus->big_radius, 2) * pow(p, 2)));
// 	d = ((4 * n * o) - (4 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * n) + (8 * pow(torus->big_radius, 2) * p * q));
// 	e = ((pow(o, 2)) - (2 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * o) + (4 * pow(torus->big_radius, 2) * pow(q, 2)) + pow((pow(torus->big_radius, 2) - pow(torus->small_radius, 2)), 2));
// 	//printf("**%f  %f**\n", b, d);
// 	if (b == 0 && d == 0)
// 	{
// 		ft_putendl("LOL");
// 		discriminant = (c * c) - 4 * a * e;
// 		if (discriminant < 0)
// 			return (0);
// 		else
// 		{
// 			if (discriminant == 0)
// 				data->solution = - c;
// 			else
// 			{
// 				discriminant = sqrt(discriminant);
// 				s1 = sqrt((- c + discriminant));
// 				s2 = sqrt((- c - discriminant));
// 				data->solution = (s1 < s2) ? s1 : s2;
// 			}
// 		}
// 	}
// 	else if (b != 0 && a * pow(d, 2) == e * pow(b, 2))
// 		printf("LOL\n");
// 	tmp_node = v_double_mult(&data->current_rayon, data->solution);
// 	torus->node = v_v_add(&data->current_origin, &tmp_node);
// 	tmp = v_v_subs(&torus->node, &torus->center);
// 	k = dot_product(&tmp, &torus->axis);
// 	tmp = v_double_mult(&torus->axis, k);
// 	r = v_v_subs(&torus->node, &tmp);
// 	s = sqrt(pow(torus->small_radius, 2) - pow(k, 2));
// 	torus->node_normal = v_v_subs(&torus->node, &r);
// 	tmp = v_v_subs(&torus->center, &r);
// 	tmp = v_double_mult(&tmp, s);
// 	tmp = v_double_div(&tmp, torus->big_radius + s);
// 	torus->node_normal = v_v_subs(&torus->node_normal, &tmp);
// 	torus->node_normal = normalize(&torus->node_normal);
// 		return (1);
// }

int sort_type(t_env *e, t_object *object)
{
	int intersect;

	intersect = 0;
	if (!(ft_strcmp(object->type, "plane")))
		intersect = plane_intersection(e, object);
	else if (!(ft_strcmp(object->type, "sphere")))
		intersect = sphere_intersection(e, object);
	else if (!(ft_strcmp(object->type, "cylinder")))
		intersect = cylinder_intersection(e, object);
	else if (!(ft_strcmp(object->type, "cone")))
		intersect = cone_intersection(e, object);
	return (intersect);	
}

void check_intersection(t_env *e, t_object *object)
{
	while (object)
	{
		if (sort_type(e, object) && e->solution < e->distance)
		{
			e->distance = e->solution; 
			e->current_node = object->node;
			e->current_node_normal = object->node_normal;
			e->current_color = object->color;

			e->reflect = object->reflect;
			e->refract = object->refract;
			e->id_object = object->id;

			e->intersect = 1;
		}
		object = object->next;
	}
}

int		check_if_light_is_blocked(t_env *e)
{
	t_object *tmp_object;

	tmp_object = e->object;
	while (tmp_object)
	{
		if (tmp_object->id != e->id_object 
			&& sort_type(e, tmp_object) && e->solution < e->distance_light_object)
				return (1);
		tmp_object = tmp_object->next;
	}
	return (0);
}

