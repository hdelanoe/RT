/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:58:42 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 11:58:44 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cone		*add_new_cone(t_object *object, t_cone *new_cone)
{
	t_cone	*tmp;

	tmp = object->start_cone;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cone;
		new_cone->next = NULL;
	}
	else
		object->start_cone = new_cone;
	return (tmp);
}

void		create_cone(t_object *object, t_json *json)
{
	t_cone	*cone;

	while (json->member)
	{
		cone = (t_cone*)ft_memalloc(sizeof(t_cone));
		cone->id = ft_atod(json->member->name);
		while(json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "vertex") == 0)
				cone->vertex = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "tangent") == 0)
				cone->tangent = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "lenght") == 0)
				cone->lenght_max = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "axis") == 0)
				cone->axis = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				cone->color = parse_color(json->member->member->member);
			json->member->member = json->member->member->next;
		}
		cone = add_new_cone(object, cone);
		json->member = json->member->next;
	}
}

int		cone_intersection(t_datas *d, t_cone *cone)
{
	t_poly 	p;
	t_inter i;

	i.object_rayon = v_v_subs(&d->current_origin, &cone->vertex);
	p.tmp1 = (1 + pow(cone->tangent, 2));
	p.tmp2 = dot_product(&d->current_rayon, &cone->axis);
	p.tmp3 = dot_product(&i.object_rayon, &cone->axis);

	p.a = 1 - (p.tmp1 * pow(p.tmp2, 2));
	p.b = 2 * ((dot_product(&i.object_rayon, &d->current_rayon) - (p.tmp1 * (p.tmp2 * p.tmp3))));
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (p.tmp1 * (p.tmp3 * p.tmp3));
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	if (p.discriminant < 0)
		return (0);
	else
	{
		if (p.discriminant == 0)
			d->solution = - (p.b / (2 * p.a));
		else
		{
			p.discriminant = sqrt(p.discriminant);
			p.s1 = (- p.b + p.discriminant) / (2 * p.a);
			p.s2 = (- p.b - p.discriminant) / (2 * p.a);
			d->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
		}
		i.tmp_node = v_double_mult(&d->current_rayon, d->solution);
		cone->node = v_v_add(&d->current_origin, &i.tmp_node);

		p.len = (p.tmp2 * d->solution) + p.tmp3;
		if (p.len > cone->lenght_max || p.len < 0)
			return (0);
		i.tmp_node_normal1 = v_v_subs(&cone->node, &cone->vertex);
		i.tmp_node_normal2 = v_double_mult(&cone->axis, p.len);
		i.tmp_node_normal2 = v_double_mult(&i.tmp_node_normal2, p.tmp1);
		cone->node_normal = v_v_subs(&i.tmp_node_normal1, &i.tmp_node_normal2);
		cone->node_normal = normalize(&cone->node_normal);
		return (1);
	}
}

void 	blocked_by_a_cone(t_datas *d, int *light_blocked, t_object *object)
{
	t_cone	*tmp_cone;

	tmp_cone = object->start_cone;
	while (tmp_cone)
	{
		if (tmp_cone->id != d->id_cone)
		{
			if (cone_intersection(d, tmp_cone))
			{
				if (d->solution < d->distance_light_object)
				{
					*light_blocked = 1;
					break;
				}
			}
		}
		tmp_cone = tmp_cone->next;
	}
}