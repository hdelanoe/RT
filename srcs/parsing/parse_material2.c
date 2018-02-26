/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 17:27:05 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:27:06 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_material(t_object *object, t_json *tmp)
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
}
