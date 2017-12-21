/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:00:25 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/07 16:22:50 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double get_content_from_member(char *name, t_json **membre)
{
	t_json *tmp;

	tmp = (*membre);
	while (tmp)
	{
		if(ft_strcmp(tmp->name, name) == 0)
			return (ft_atod(tmp->content));
		tmp = tmp->next;
	}
	return (0);  /// ERREUR : Manque une donnée
}

t_vector parse_point(t_json *membre)
{
	double x;
	double y;
	double z;

	x = get_content_from_member("x", &membre);
	y = get_content_from_member("y", &membre);
	z = get_content_from_member("z", &membre);
	return (set_vector(x, y, z));
}

t_vector parse_normal(t_json *membre)
{
	t_vector to_norm;

	to_norm = parse_point(membre);
	to_norm = normalize(&to_norm);
	return (to_norm);
}

t_color  parse_color(t_json *membre)
{
	double r;
	double g;
	double b;

	r = get_content_from_member("r", &membre);
	g = get_content_from_member("g", &membre);
	b = get_content_from_member("b", &membre);
	return (set_color(b, g, r));
}

void debug_plane(t_object *tmp)
{
	printf("PLANE:\n");
	printf("coord :  x->%f\n", tmp->point.x);
	printf("         y->%f\n", tmp->point.y);
	printf("         z->%f\n", tmp->point.z);
	printf("normal : x->%f\n", tmp->normal.x);
	printf("         y->%f\n", tmp->normal.y);
	printf("         z->%f\n", tmp->normal.z);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}
