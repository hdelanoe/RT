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

#include "rtv1.h"

void		parse_scene(t_env *e, t_json *json)
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
		e->recursion = ft_atoi(json->content) > 6 ?
					e->recursion : ft_atoi(json->content);
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
	object->indice = R_TEST;
	return (object);
}

void		parse_indice(char **material, t_object *object)
{
	if (!(ft_strcmp(*material, "void")))
		object->indice = R_VOID;
	else if (!(ft_strcmp(*material, "air")))
		object->indice = R_AIR;
	else if (!(ft_strcmp(*material, "ice")))
		choose_ice(object);
	else if (!(ft_strcmp(*material, "water")))
		choose_water(object);
	else if (!(ft_strcmp(*material, "pmma")))
		choose_pmma(object);
	else if (!(ft_strcmp(*material, "glass")))
		choose_glass(object);
	else if (!(ft_strcmp(*material, "diam")))
		choose_diam(object);
	else if (!(ft_strcmp(*material, "mirror")))
		choose_mirror(object);
	else if (!(ft_strcmp(*material, "marbre")))
		choose_marbre(object);
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
	free((*member));
}
