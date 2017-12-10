/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:57:47 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 11:57:50 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere		*add_new_sphere(t_object *object, t_sphere *new_sphere)
{
	t_sphere	*tmp;

	tmp = object->start_sphere;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere;
		new_sphere->next = NULL;
	}
	else
		object->start_sphere = new_sphere;
	return (tmp);
}


void debug_sphere(t_sphere *tmp)
{
	printf("SPHERE:\n");
	printf("coord :  x->%f\n", tmp->center.x);
	printf("         y->%f\n", tmp->center.y);
	printf("         z->%f\n", tmp->center.z);
	printf("radius ->%f\n", tmp->radius);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}


void		create_sphere(t_object *object, t_json *json)
{
	t_sphere	*sphere;

	while (json->member)
	{
		sphere = (t_sphere*)ft_memalloc(sizeof(t_sphere));
		sphere->id = ft_atoi(json->member->name);
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				sphere->center = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "radius") == 0)
				sphere->radius = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				sphere->color = parse_color(json->member->member->member);
			json->member->member = json->member->member->next;
		}
		debug_sphere(sphere);
		sphere = add_new_sphere(object, sphere);
		json->member = json->member->next;
	}
}

int		sphere_intersection(t_datas *d, t_sphere *sphere)
{
	t_poly 	p;
	t_inter i;

	i.object_rayon = v_v_subs(&d->current_origin, &sphere->center);
	p.b = dot_product(&i.object_rayon, &d->current_rayon);
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (sphere->radius * sphere->radius);
	if(!(poly_2nd_degree_sphere(d, &p)))
		return (0);
	i.tmp_node = v_double_mult(&d->current_rayon, d->solution);
	sphere->node = v_v_add(&d->current_origin, &i.tmp_node);
	sphere->node_normal = v_v_subs(&sphere->node, &sphere->center);
	sphere->node_normal = normalize(&sphere->node_normal);
	return (1);
}

void 	blocked_by_a_sphere(t_datas *d, int *light_blocked, t_object *object)
{
	t_sphere	*tmp_sphere;

	tmp_sphere = object->start_sphere;
	while (tmp_sphere)
	{
		if (tmp_sphere->id != d->id_sphere)
		{
			if (sphere_intersection(d, tmp_sphere))
			{
				if (d->solution < d->distance_light_object)
				{
					*light_blocked = 1;
					break;
				}
			}
		}
		tmp_sphere = tmp_sphere->next;
	}
}
