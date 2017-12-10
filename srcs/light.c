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

void debug_light(t_light *tmp)
{
	printf("LIGHT:\n");
	printf("origin : x->%f\n", tmp->origin.x);
	printf("         y->%f\n", tmp->origin.y);
	printf("         z->%f\n", tmp->origin.z);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}
void			create_light(t_object *object, t_json *json)
{
	t_light	*light;

	while (json->member)
	{
		light = ft_memalloc(sizeof(t_light));
		light->next = NULL;
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				light->origin = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				light->color = parse_color(json->member->member->member);
			json->member->member = json->member->member->next;
		}
		debug_light(light);
		light = add_new_light(object, light);
		json->member = json->member->next;
	}
}