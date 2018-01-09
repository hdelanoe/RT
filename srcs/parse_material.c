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

void	init_material(t_object *object)
{
	object->color = set_color(0.5, 0.5, 0.5);
	object->ambient = 0.125;
	object->diffuse = 0.875;
	object->specular = 0.9;
	object->reflect = 0;
	object->refract = 0;
	object->absorbtion = 0;
}

void	parse_material(t_json *material, t_object *object)
{
	t_json *tmp;

	while (material->member)
	{
		if (ft_strcmp(material->member->name, "color") == 0)
			object->color = parse_color(material->member->member);
		else 
		{
			if (ft_strcmp(material->member->name, "ambient") == 0)
				object->ambient = ft_atod(material->member->content);
			else if (ft_strcmp(material->member->name, "diffuse") == 0)
				object->diffuse = ft_atod(material->member->content);
			else if (ft_strcmp(material->member->name, "specular") == 0)
				object->specular = ft_atod(material->member->content);
			else if (ft_strcmp(material->member->name, "reflect") == 0)
				object->reflect = ft_atod(material->member->content);
			else if (ft_strcmp(material->member->name, "refract") == 0)
				object->refract = ft_atod(material->member->content);
			else if (ft_strcmp(material->member->name, "absorbtion") == 0)
				object->absorbtion = ft_atod(material->member->content);
			else
				exit_parser(1);
			free(material->member->content);
		}
		free(material->member->name);
		tmp = material->member;
		material->member = material->member->next;
		free(tmp);
	}
}