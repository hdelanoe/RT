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

void 	plane_attribut(t_object *plane, t_json *json)
{
	if (!(ft_strcmp(json->name, "coord")) && json->member)
		plane->point = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "color")) && json->member)
		plane->color = parse_color(json->member);
	else if (!(ft_strcmp(json->name, "normal")) && json->member)
		plane->normal = parse_normal(json->member);
	else if (!(ft_strcmp(json->name, "material")))
		parse_material(json, plane);
	else
		ft_printf("{R}WARNING:{E} plane as a bad attribut\n");
}

void	sphere_attribut(t_json *tmp, t_object *sphere)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		sphere->center = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
		sphere->radius = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		sphere->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "plan_cut")) && tmp->member)
	{
		sphere->cap = 1;
		sphere->normal = parse_normal(tmp->member);
	}
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, sphere);
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
