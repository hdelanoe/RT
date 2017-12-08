/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:01:18 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 12:01:20 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		*add_new_light(t_object *object, t_light *new_light)
{
	t_light		*tmp;

	tmp = object->start_light;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
		new_light->next = NULL;
	}
	else
		object->start_light = new_light;
	return (tmp);
}

void			create_light(t_object *object, t_json *json)
{
	t_light	*light;
	t_json		*tmp;

	while (json->member)
	{
		light = (t_light*)ft_memalloc(sizeof(t_light));
		tmp = json->member->member;
		light->origin = set_vector(ft_atod(tmp->member->content),
		ft_atod(tmp->member->next->content), ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;	
		light->color = set_color(ft_atod(tmp->member->content), ft_atod(tmp->member->next->content), ft_atod(tmp->member->next->next->content));
//		tmp = tmp->next;
//		light->id = ft_atoi(tmp->content);
		light = add_new_light(object, light);
		json->member = json->member->next;
	}
}