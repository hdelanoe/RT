/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_material2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:12:17 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:59 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_mirror(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.7;
	object->specular = 0.9;
	object->reflect = 1;
	object->refract = 0;
}

void	choose_metal(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.9;
	object->specular = 1.5;
	object->reflect = 1;
	object->refract = 0;
}

void	choose_marble(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.725;
	object->specular = 0.9;
	object->reflect = 0;
	object->refract = 0;
	object->absorbtion = 0.8;
	object->bump = 2;
}

void	choose_snow(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.7;
	object->specular = 0;
	object->reflect = 0;
	object->refract = 0;
	object->absorbtion = 0.8;
	object->texture = 1;
}

void	choose_arc(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->sun = 1;
}
