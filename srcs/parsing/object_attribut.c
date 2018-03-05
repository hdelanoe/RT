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

#include "rt.h"

void		plane_attribut(t_object *plane, t_json *json)
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

void		sphere_attribut(t_json *tmp, t_object *sphere)
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
	else
		ft_printf("{R}WARNING:{E} sphere as a bad attribut\n");
}

void		cylinder_attribut(t_object *object, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		object->center = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		object->axis = parse_normal(tmp->member);
	else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
		object->radius = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
		object->lenght_max = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		object->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, object);
	else
		ft_printf("{R}WARNING:{E} cylinder's %s is a bad attribut\n",
			tmp->name);
}

void		cone_attribut(t_object *object, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		object->center = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "tangent")) && tmp->content)
		object->tangent = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "maxlength")) && tmp->content)
		object->lenght_max = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "minlength")) && tmp->content)
		object->radius = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		object->axis = parse_normal(tmp->member);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		object->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, object);
	else
		ft_printf("{R}WARNING:{E} cone as a bad attribut\n");
}

void		cube_attribut(t_object *cb, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		cb->point = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "width")) && tmp->content)
		cb->lenght_max = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
		cb->tangent = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "height")) && tmp->content)
		cb->radius = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		cb->axis = parse_normal(tmp->member);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		cb->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, cb);
	else
		ft_printf("{R}WARNING:{E} cube's %s is a bad attribut\n",
			tmp->name);
}
