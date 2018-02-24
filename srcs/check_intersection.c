/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/01 12:07:46 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			get_object_values(t_env *e, t_object *object, t_object *parent)
{
	if (!ft_strcmp(object->type, "area_light"))
		e->area_light_on = 1;
	else
		e->area_light_on = 0;
	e->current_node = object->node;
	e->current_node_normal = object->node_normal;
	e->bump = object->bump;
	e->current_color = object->color;
	e->ambient = object->ambient;
	e->diffuse = object->diffuse;
	e->specular = object->specular;
	e->reflect = object->reflect;
	e->refract = object->refract;
	e->specular = object->specular;
	e->absorbtion = object->absorbtion;
	e->id_object = object->id;
	if (parent && (e->is_copy || e->is_delete))
		e->id_object = parent->id;
	e->object_indice = object->indice;
}

int				sort_type(t_env *e, t_object *object)
{
	int intersect;

	intersect = 0;
	if (!(ft_strcmp(object->type, "plane")))
		intersect = plane_intersection(e, object);
	else if (!(ft_strcmp(object->type, "triangle")))
		intersect = triangle_intersection(e, object, object);
	else if (!(ft_strcmp(object->type, "quad")))
		intersect = quad_intersection(e, object);
	else if (!(ft_strcmp(object->type, "sphere")))
		intersect = sphere_intersection(e, object);
	else if (!(ft_strcmp(object->type, "cylinder")))
		intersect = cylinder_intersection(e, object);
	else if (!(ft_strcmp(object->type, "cone")))
		intersect = cone_intersection(e, object);
	else if (!(ft_strcmp(object->type, "disk")))
		intersect = disk_intersection(e, object);
	else if (!(ft_strcmp(object->type, "area_light")))
		intersect = quad_intersection(e, object);
	return (intersect);
}

void			check_intersection(t_env *e, t_object *object,
				t_object *parent)
{
	t_object	sub;
	int			flag;

	flag = 0;
	if (sort_type(e, object) && e->solution < e->distance &&
		e->solution >= 0 && fabs(e->distance - e->solution) > 0.001)
	{
		e->distance = e->solution;
		get_object_values(e, object, parent);
		if (e->text_flag == 1)
			wrap_obj(e, object, parent);
		e->intersect = 1;
	}
	if (object && object->sub_object)
	{
		sub = *object->sub_object;
		while (1)
		{
			check_intersection(e, &sub, object);
			if (sub.next == NULL)
				break ;
			sub = *sub.next;
		}
	}
}

int				light_sub_intersection(t_env *e, t_light *light,
										t_object *object, t_color *c)
{
	t_color			tmp;
	t_object		sub;

	sub = *object->sub_object;
	while (1)
	{
		if (sub.id != e->id_object && ft_strcmp(sub.type, "area_light")
		&& sort_type(e, &sub) && e->solution < e->distance_light_object
		&& fabs(e->solution - e->distance_light_object) > 0.001)
		{
			if (sub.refract == 0)
				return (1);
			tmp = c_double_mult(&e->current_color, 1 -
			sub.absorbtion);
			(*c) = c_c_mult(&light->color, &tmp);
		}
		if (sub.next == NULL)
			break ;
		sub = *sub.next;
	}
	return (0);
}

t_color			light_intersection(t_env *e, t_light *light)
{
	t_object		tmp_object;
	t_color			tmp;

	tmp_object = *e->object;
	e->tmp_clr = set_color(light->color.b, light->color.g, light->color.r);
	while (1)
	{
		if (tmp_object.id != e->id_object
		&& ft_strcmp(tmp_object.type, "area_light")
		&& sort_type(e, &tmp_object) && e->solution < e->distance_light_object
		&& fabs(e->solution - e->distance_light_object) > 0.001)
		{
			if (tmp_object.refract == 0)
				return (set_color(0, 0, 0));
			tmp = c_double_mult(&tmp_object.color, 1 - tmp_object.absorbtion);
			e->tmp_clr = c_c_mult(&light->color, &tmp);
		}
		if (tmp_object.sub_object != NULL && light_sub_intersection(e,
		light, &tmp_object, &e->tmp_clr))
			return (set_color(0, 0, 0));
		if (tmp_object.next == NULL)
			break ;
		tmp_object = *tmp_object.next;
	}
	return (e->tmp_clr);
}
