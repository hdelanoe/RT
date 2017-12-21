/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:01:18 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 12:01:20 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		add_new_light(t_light **list, t_light *new_light)
{
	t_light	*tmp;

	if (!(*list)->color.r)
	{
		(*list) = new_light;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_light;
	(*list) = tmp;

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
void			create_light(t_env *e, t_json *json)
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
		add_new_light(&e->light, light);
		json->member = json->member->next;
	}
}