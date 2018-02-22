/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:22 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:19:41 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	choose_ice(t_object *object)
{
	object->ambient = 0.4;
	object->diffuse = 0.625;
	object->specular = 0.8;
	object->reflect = 1;
	object->refract = 0;
	object->absorbtion = 0.725;
	object->bump = 1;
	object->indice = R_ICE;
}

void	choose_water(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.725;
	object->specular = 0.7;
	object->reflect = 1;
	object->refract = 1;
	object->absorbtion = 0.325;
	object->bump = 1;
	object->indice = R_WATER;
}

void	choose_pmma(t_object *object)
{
	object->ambient = 0.5;
	object->diffuse = 0.625;
	object->specular = 0.7;
	object->reflect = 1;
	object->refract = 1;
	object->absorbtion = 0.8;
	object->indice = R_PMMA;
}

void	choose_glass(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.875;
	object->specular = 0.8;
	object->reflect = 1;
	object->refract = 1;
	object->absorbtion = 0.425;
	object->indice = R_GLASS;
}

void	choose_diam(t_object *object)
{
	object->ambient = 0.3;
	object->diffuse = 0.9;
	object->specular = 0.9;
	object->reflect = 1;
	object->refract = 1;
	object->absorbtion = 0.125;
	object->indice = R_DIAM;
}
