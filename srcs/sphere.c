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

void		add_new_object(t_object **list, t_object *new_object)
{
	t_object	*tmp;

	if (!(*list)->type)
	{
		(*list) = new_object;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_object;
	(*list) = tmp;

}


void debug_sphere(t_object *tmp)
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


void		create_sphere(t_env *e, t_json *json)
{
	t_object	*sphere;

	while (json->member)
	{
		sphere = (t_object*)ft_memalloc(sizeof(t_object));
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
		sphere->type = ft_strdup("sphere");
		sphere->reflect = 0;
		sphere->refract = 1;
		add_new_object(&e->object, sphere);
		json->member = json->member->next;
	}
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
	else
	{
		if (p.discriminant == 0)
			e->solution = - p.b;
		else
		{
			p.discriminant = sqrt(p.discriminant);
			p.s1 = (- p.b + p.discriminant);
			p.s2 = (- p.b - p.discriminant);
			e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
		}
		i.tmp_node = v_double_mult(&e->current_rayon, e->solution);
		sphere->node = v_v_add(&e->current_origin, &i.tmp_node);
		sphere->node_normal = v_v_subs(&sphere->node, &sphere->center);
		sphere->node_normal = normalize(&sphere->node_normal);
	}
	return (1);
}
