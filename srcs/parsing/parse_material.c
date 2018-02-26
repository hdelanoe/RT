/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 12:44:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:20:11 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_scene(t_env *e, t_json *json)
{
	if (!(ft_strcmp(json->name, "camera_origin")) && json->member)
		e->camera.origin = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "camera_lookat")) && json->member)
		e->lookat = parse_point(json->member);
	else if (!(ft_strcmp(json->name, "window_width")) && json->content)
		e->width = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "window_height")) && json->content)
		e->height = ft_atod(json->content);
	else if (!(ft_strcmp(json->name, "recursion")) && json->content)
	{
		e->recursion = ft_atoi(json->content);
		e->recursion = e->recursion >= 9 ? 6 : e->recursion;
	}
	else
	{
		ft_printf("{R}WARNING:{E} %s is not valid\n", json->name);
		exit_parser(1);
	}
}

t_object	*init_material(void)
{
	t_object *object;

	if (!(object = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Error in malloc object");
	object->id = -1;
	object->color = set_color(0.5, 0.5, 0.5);
	object->ambient = 0.3;
	object->diffuse = 0.875;
	object->specular = 0.9;
	object->reflect = 0;
	object->refract = 0;
	object->absorbtion = 0.125;
	object->radius = 0;
	object->sub_object = NULL;
	object->bump = 0;
	object->texture = 0;
	object->indice = R_TEST;
	return (object);
}

void		parse_material(t_json *material, t_object *object)
{
	t_json	*tmp;

	if (material->content)
		parse_indice(&material->content, object);
	if (!material->member)
		return ;
	while (material->member)
	{
		tmp = material->member;
		check_material(object, tmp);
		material->member = material->member->next;
		free_json_member(&tmp);
	}
}

void		free_json_member(t_json **member)
{
	free((*member)->name);
	free((*member)->content);
	if ((*member)->member)
		free_content((*member)->member);
	free((*member));
}
