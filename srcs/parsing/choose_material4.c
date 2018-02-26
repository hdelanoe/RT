/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_material4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:12:17 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:59 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_moon(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 8;
}

void	choose_mars(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 9;
}

void	choose_mercury(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 10;
}

void	choose_jupiter(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 11;
}

void	choose_venus(t_object *object)
{
	object->ambient = 1;
	object->specular = 0;
	object->absorbtion = 0.8;
	object->texture = 12;
}
