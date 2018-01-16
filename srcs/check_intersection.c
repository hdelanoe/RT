/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_object_values(t_env *e, t_object *object)
{
	e->current_node = object->node;
	e->current_node_normal = object->node_normal;
	e->current_color = object->color;
	e->ambient = object->ambient;
	e->diffuse = object->diffuse;
	e->specular = object->specular;
	e->reflect = object->reflect;
	e->refract = object->refract;
	e->specular = object->specular;
	e->id_object = object->id;
	if (e->is_copy)
		e->copy = object;
}

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
	else if (!(ft_strcmp(object->type, "disk")))
		intersect = disk_intersection(e, object);
	return (intersect);	
}

void check_intersection(t_env *e, t_object *object)
{
	while (object)
	{
		if (sort_type(e, object) && e->solution < e->distance && e->solution >= 0)
		{
			e->distance = e->solution;
			get_object_values(e, object);
			if (!(ft_strcmp("plane", object->type)))
				e->bump = 1;

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
		if (tmp_object->id != e->id_object// && tmp_object->refract == 0
			&& sort_type(e, tmp_object) && e->solution < e->distance_light_object)
				return (1);
		tmp_object = tmp_object->next;
	}
	return (0);
}

