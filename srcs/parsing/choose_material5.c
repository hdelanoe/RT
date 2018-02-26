/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_material5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:12:17 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:59 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_space(t_object *object)
{
	object->ambient = 1;
	object->skybox = 1;
	object->texture = 2;
}

void	choose_saturn(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 13;
}

void	choose_neptune(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 14;
}

void	choose_uranus(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 15;
}

void	choose_cloud(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.1;
	object->texture = 16;
}
