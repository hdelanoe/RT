/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_material3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:12:17 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:59 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_paradise(t_object *object)
{
	object->ambient = 1;
	object->skybox = 1;
	object->texture = 3;
}

void	choose_cave(t_object *object)
{
	object->ambient = 1;
	object->skybox = 1;
	object->texture = 4;
}

void	choose_space(t_object *object)
{
	object->ambient = 1;
	object->skybox = 1;
	object->texture = 2;
}

void	choose_sun(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->texture = 5;
	object->sun = 1;
}

void	choose_iron(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 7;
}
