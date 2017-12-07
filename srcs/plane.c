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

void	create_plane(t_object *object, t_json *json)
{
	t_plane		*plane;
	t_json		*tmp;

	while (json->member)
	{
		plane = (t_plane*)ft_memalloc(sizeof(t_plane));
		tmp = json->member->member;
		plane->point = set_vector(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;
		plane->normal = set_vector(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		plane->normal = normalize(&plane->normal);
		tmp = tmp->next;
		plane->color = set_color(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;
		plane->id = ft_atoi(tmp->content);
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
