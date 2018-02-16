/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:24:05 by etranchi          #+#    #+#             */
/*   Updated: 2017/12/10 19:24:06 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_paraboloid	*add_new_paraboloid(t_object *object,
									t_paraboloid *new_paraboloid)
{
	t_paraboloid *tmp;

	tmp = object->start_paraboloid;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_paraboloid;
		new_paraboloid->next = NULL;
	}
	else
		object->start_paraboloid = new_paraboloid;
	return (tmp);
}

void			debug_paraboloid(t_paraboloid *tmp)
{
	printf("PARABOLOID:\n");
	printf("coord :  x->%f\n", tmp->origin.x);
	printf("         y->%f\n", tmp->origin.y);
	printf("         z->%f\n", tmp->origin.z);
	printf("normale : x->%f\n", tmp->normal.x);
	printf("         y->%f\n", tmp->normal.y);
	printf("         z->%f\n", tmp->normal.z);
	printf("distance ->%f\n", tmp->distance);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}

void			create_paraboloid(t_object *object, t_json *json)
{
	t_paraboloid *paraboloid;

	while (json->member)
	{
		paraboloid = (t_paraboloid *)ft_memalloc(sizeof(t_paraboloid));
		paraboloid->id = ft_atoi(json->member->name);
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord"))
				paraboloid->origin = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "normal"))
				paraboloid->normal = parse_normal(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "colors"))
				paraboloid->color = parse_color(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "distance"))
				paraboloid->distance = ft_atod(json->member->member->content);
			json->member->member = json->member->member->next;
		}
		debug_paraboloid(paraboloid);
		paraboloid = add_new_paraboloid(object, paraboloid);
		json->member = json->member->next;
	}
}
