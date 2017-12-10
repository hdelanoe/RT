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

t_plane	*add_new_plane(t_object *object, t_plane *new_plane)
{
	t_plane		*tmp;

	tmp = object->start_plane;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_plane;
		new_plane->next = NULL;
	}
	else
		object->start_plane = new_plane;
	return (tmp);
}

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

void debug_plane(t_plane *tmp)
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
void		create_plane(t_object *object, t_json *json)
{
	t_plane		*plane;

	while (json->member)
	{
		plane = (t_plane*)ft_memalloc(sizeof(t_plane));
		plane->id = ft_atoi(json->member->name);
		while(json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				plane->point = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "normal") == 0)
				plane->normal = parse_normal(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				plane->color = parse_color(json->member->member->member);
			json->member->member = json->member->member->next;
		}
		debug_plane(plane);
		plane = add_new_plane(object, plane);
		json->member = json->member->next;
	}
}

int		plane_intersection(t_datas *d, t_plane *plane)
{
	double		a;
	double		b;
	double		s;
	t_vector	plan_cam;
	t_vector	tmp_node;

	plan_cam = v_v_subs(&d->current_origin, &plane->point);
	a = dot_product(&plane->normal, &d->current_rayon);
	b = dot_product(&plane->normal, &plan_cam);
	if (a == 0)
		return (0);
	s = -(b / a);
	if (s < 0)
		return (0);
	else
	{
		d->solution = s;
		tmp_node = v_double_mult(&d->current_rayon, d->solution);
		plane->node = v_v_add(&d->current_origin, &tmp_node);
		if (a < 0)
			plane->node_normal = plane->normal;
		else
			plane->node_normal = v_double_mult(&plane->normal, (-1));
		return (1);
	}
}

void	blocked_by_a_plane(t_datas *d, int *light_blocked, t_object *object)
{
	t_plane	*tmp_plane;

	tmp_plane = object->start_plane;
	while (tmp_plane)
	{
		if (tmp_plane->id != d->id_plane)
		{
			if (plane_intersection(d, tmp_plane))
			{
				if (d->solution < d->distance_light_object)
				{
					*light_blocked = 1;
					break ;
				}
			}
		}
		tmp_plane = tmp_plane->next;
	}
}
