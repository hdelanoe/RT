/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 12:44:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/17 17:20:11 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_indice3(char **material, t_object *object)
{
	if (!(ft_strcmp(*material, "neptune")))
		choose_neptune(object);
	else if (!(ft_strcmp(*material, "uranus")))
		choose_uranus(object);
	else if (!(ft_strcmp(*material, "cloud")))
		choose_cloud(object);
	else if (!(ft_strcmp(*material, "paradise")))
		choose_paradise(object);
	else if (!(ft_strcmp(*material, "arc")))
		choose_arc(object);
	else
		ft_printf("{R}WARNING:{E} material %s is not valid\n", *material);
}

void		parse_indice2(char **material, t_object *object)
{
	if (!(ft_strcmp(*material, "space")))
		choose_space(object);
	else if (!(ft_strcmp(*material, "cave")))
		choose_cave(object);
	else if (!(ft_strcmp(*material, "sun")))
		choose_sun(object);
	else if (!(ft_strcmp(*material, "earth")))
		choose_earth(object);
	else if (!(ft_strcmp(*material, "iron")))
		choose_iron(object);
	else if (!(ft_strcmp(*material, "moon")))
		choose_moon(object);
	else if (!(ft_strcmp(*material, "mars")))
		choose_mars(object);
	else if (!(ft_strcmp(*material, "mercury")))
		choose_mercury(object);
	else if (!(ft_strcmp(*material, "jupiter")))
		choose_jupiter(object);
	else if (!(ft_strcmp(*material, "venus")))
		choose_venus(object);
	else if (!(ft_strcmp(*material, "saturn")))
		choose_saturn(object);
	else
		parse_indice3(material, object);
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
	else if (!(ft_strcmp(*material, "metal")))
		choose_metal(object);
	else if (!(ft_strcmp(*material, "marble")))
		choose_marble(object);
	else if (!(ft_strcmp(*material, "snow")))
		choose_snow(object);
	else
		parse_indice2(material, object);
}
