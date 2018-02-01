/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_area_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:23 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/21 15:35:24 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			create_area_light(t_env *e, t_json *json)
{
	t_light		*al_light;
	t_object	*al_object;
	t_json 		*tmp;

	if(!(al_light = ft_memalloc(sizeof(t_light))))
		exit_rt(1);
	if (!(al_light->type = ft_strdup("area_light")))
		exit_rt(1);
	if (!(al_object = (t_object*)ft_memalloc(sizeof(t_object))))
		exit_rt(1);
	if (!(al_object->type = ft_strdup("area_light")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord_1")) && tmp->member)
		{
			al_object->point = parse_point(tmp->member);
			al_light->point = parse_point(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "coord_2")) && tmp->member)
		{
			al_object->point_2 = parse_point(tmp->member);
			al_light->point_2 = parse_point(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "coord_3")) && tmp->member)
		{
			al_object->point_3 = parse_point(tmp->member);
			al_light->point_3 = parse_point(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "coord_4")) && tmp->member)
		{
			al_object->point_4 = parse_point(tmp->member);
			al_light->point_4 = parse_point(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		{
			al_object->color = parse_color(tmp->member);
			al_light->color = parse_color(tmp->member);
		}
		else
			ft_printf("area_light %d as a bad attribut\n", al_light->id);
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_light(al_light);
	add_new_light(&e->light, area_light);
	debug_object(al_object);
	add_new_object(&e->object, area_light);
}
