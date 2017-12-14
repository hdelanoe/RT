/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
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
		if(ft_strcmp(tmp->name, name) == 0 )
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
	char *tmp;

	x = get_content_from_member((tmp = ft_strdup("x")), &membre);
	free(tmp);
	y = get_content_from_member((tmp = ft_strdup("y")), &membre);
	free(tmp);
	z = get_content_from_member((tmp = ft_strdup("z")), &membre);
	free(tmp);
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
	char *tmp;

	r = get_content_from_member((tmp = ft_strdup("r")), &membre);
	free(tmp);
	g = get_content_from_member((tmp = ft_strdup("g")), &membre);
	free(tmp);
	b = get_content_from_member((tmp = ft_strdup("b")), &membre);
	free(tmp);
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
void		create_plane(t_env *e, t_json *json)
{
	t_object	*plane;

	while (json->member)
	{
		plane = (t_object*)ft_memalloc(sizeof(t_object));
		plane->id = ft_atoi(json->member->name);
		while(json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				plane->point = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "normal") == 0)
				plane->normal = parse_normal(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				plane->color = parse_color(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "reflect") == 0)
				plane->reflect = ft_atoi(json->member->member->content);
			json->member->member = json->member->member->next;
		}
		plane->type = ft_strdup("plane");
		plane->refract = 0;
		debug_plane(plane);
		add_new_object(&e->object, plane);
		json->member = json->member->next;
	}
}

int		plane_intersection(t_env *e, t_object *plane)
{
	double		a;
	double		b;
	double		s;
	t_vector	plan_cam;
	t_vector	tmp_node;

	plan_cam = v_v_subs(&e->current_origin, &plane->point);
	a = dot_product(&plane->normal, &e->current_rayon);
	b = dot_product(&plane->normal, &plan_cam);
	if (a == 0)
		return (0);
	s = -(b / a);
	if (s < 0)
		return (0);
	else
	{
		e->solution = s;
		tmp_node = v_double_mult(&e->current_rayon, e->solution);
		plane->node = v_v_add(&e->current_origin, &tmp_node);
		if (a < 0)
			plane->node_normal = plane->normal;
		else
			plane->node_normal = v_double_mult(&plane->normal, (-1));
		return (1);
	}
}