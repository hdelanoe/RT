/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_attribut.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:14:22 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/06 16:14:23 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 	plane_attribut(t_object *object, t_json *json)
{
	if (!(ft_strcmp(json->name, "coord")) && json->member)
		object->point = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "color")) && json->member)
		object->color = parse_color(json->member);
	else if (!(ft_strcmp(json->name, "normal")) && json->member)
		object->normal = parse_normal(json->member);
	else if (!(ft_strcmp(json->name, "material")))
		parse_material(json, object);
	else
		ft_printf("{R}WARNING:{E} plane as a bad attribut\n");
}

t_object 	*sphere_attribut(t_object *object, t_json *json)
{
	if (!(ft_strcmp(json->name, "coord")) && json->member)
		object->point = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "color")) && json->member)
		object->color = parse_color(json->member);
	else if (!(ft_strcmp(json->name, "radius")) && json->content)
		object->radius = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "material")))
		parse_material(json, object);
	else if (!(ft_strcmp(json->name, "plan_cut")) && json->member)
	{
		object->normal = parse_normal(json->member);
		create_cap_sphere(object);
	}
	else
		ft_printf("{R}WARNING:{E} sphere as a bad attribut\n");
	return (object);
}

void 	cylinder_attribut(t_object *object, t_json *json)
{
	if (!(ft_strcmp(json->name, "coord")) && json->member)
		object->point = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "color")) && json->member)
		object->color = parse_color(json->member);
	else if (!(ft_strcmp(json->name, "axis")) && json->member)
		object->axis = parse_normal(json->member);
	else if (!(ft_strcmp(json->name, "radius")) && json->content)
		object->radius = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "length")) && json->content)
	{
		object->cap = 1;
		object->lenght_max = ft_atod(json->content);
	}
	else if (!(ft_strcmp(json->name, "material")))
		parse_material(json, object);
	else
		ft_printf("{R}WARNING:{E} cylinder as a bad attribut\n");
}

void 	cone_attribut(t_object *object, t_json *json)
{
	if (!(ft_strcmp(json->name, "coord")) && json->member)
		object->point = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "color")) && json->member)
		object->color = parse_color(json->member);
	else if (!(ft_strcmp(json->name, "tangent")) &&json->content)
		object->tangent = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "maxlength")) && json->content)
	{
		object->cap = 1;
		object->lenght_max = ft_atod(json->content);
	}
	else if (!(ft_strcmp(json->name, "minlength")) && json->content)
		object->radius = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "axis")) && json->member)
	{
		object->axis = parse_point(json->member);
		object->axis = normalize(&object->axis);
	}
	else if (!(ft_strcmp(json->name, "material")))
		parse_material(json, object);
	else
		ft_printf("{R}WARNING:{E} cone as a bad attribut\n");
}
