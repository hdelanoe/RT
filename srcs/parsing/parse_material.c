/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 12:44:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/21 12:44:16 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_scene(t_env *e, t_json *json)
{
	if (!(ft_strcmp(json->name, "camera")) && json->member)
		e->camera.origin = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "width")) && json->content)
		e->camera.width = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "height")) && json->content)
		e->camera.height = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "distance")) && json->content)
		e->camera.distance = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "recursion")) && json->content)
		e->recursion = ft_atoi(json->content); 
	else
		ft_printf("{R}WARNING:{E} %s is not valid\n", json->name);
}

t_object	*init_material()
{
	t_object *object;

	if (!(object = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Error in malloc object");
	object->id = -1;
	object->color = set_color(0.5, 0.5, 0.5);
	object->ambient = 0.125;
	object->diffuse = 0.875;
	object->specular = 0.9;
	object->reflect = 0;
	object->refract = 0;
	object->absorbtion = 0.125;
	object->radius = 0;
	object->sub_object = NULL;
	return (object);
}

void	parse_material(t_json *material, t_object *object)
{
	t_json 	*tmp;

	while (material->member)
	{
		tmp = material->member;
		if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			object->color = parse_color(tmp->member);
		else 
		{
			if (!(ft_strcmp(tmp->name, "ambient")) && tmp->content)
				object->ambient = ft_atod(tmp->content);
			else if (!(ft_strcmp(tmp->name, "diffuse")) && tmp->content)
				object->diffuse = ft_atod(tmp->content);
			else if (!(ft_strcmp(tmp->name, "specular")) && tmp->content)
				object->specular = ft_atod(tmp->content);
			else if (!(ft_strcmp(tmp->name, "reflect")) && tmp->content)
				object->reflect = ft_atod(tmp->content);
			else if (!(ft_strcmp(tmp->name, "refract")) && tmp->content)
				object->refract = ft_atod(tmp->content);
			else if (!(ft_strcmp(tmp->name, "absorbtion")) && tmp->content)
				object->absorbtion = ft_atod(tmp->content);
			else
				ft_printf("{R}WARNING:{E} material %s is not valid\n", tmp->name);
			free(tmp->content);
		}
		material->member = material->member->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_json_member(t_json **member)
{
	free((*member)->name);
	free((*member)->content);
	free((*member));
}