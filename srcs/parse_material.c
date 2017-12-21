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

void	parse_material(char *material, t_object *object)
{
	if (!(ft_strcmp(material, "mirror")))
	{
		object->reflect = 1;
		object->refract = 0;
		object->refract_inc = 0.0;
	}
	else if (!(ft_strcmp(material, "glass")))
	{

		object->reflect = 0;
		object->refract = 1;
		object->refract_inc = 0.25;
	}
	else
	{
		object->reflect = 0;
		object->refract = 0;
		object->refract_inc = 0;
	}	
}