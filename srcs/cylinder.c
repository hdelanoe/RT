/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:59:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 11:59:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder		*add_new_cylinder(t_object *object, t_cylinder *new_cylinder)
{
	t_cylinder	*tmp;

	tmp = object->start_cylinder;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cylinder;
		new_cylinder->next = NULL;
	}
	else
		object->start_cylinder = new_cylinder;
	return (tmp);
}

void		create_cylinder(t_object *object, t_json *json)
{
	t_cylinder	*cylinder;
	t_json		*tmp;

	while (json->member)
	{
		cylinder = (t_cylinder*)ft_memalloc(sizeof(t_cylinder));
		cylinder->id = ft_atoi(json->member->name);
		tmp = json->member->member;
		cylinder->center = set_vector(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;	
		cylinder->radius = ft_atod(tmp->content);
		tmp = tmp->next;
		cylinder->lenght_max = ft_atod(tmp->content);
		tmp = tmp->next;
		cylinder->axis = set_vector(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		cylinder->axis = normalize(&cylinder->axis);
		tmp = tmp->next;
		cylinder->color = set_color(ft_atod(tmp->member->content),
			ft_atod(tmp->member->next->content),
			ft_atod(tmp->member->next->next->content));
		cylinder = add_new_cylinder(object, cylinder);
		json->member = json->member->next;
	}
}

int		cylinder_intersection(t_datas *d, t_cylinder *cylinder)
{
	t_poly	p;
	t_inter	i;

	i.object_rayon = v_v_subs(&d->current_origin, &cylinder->center);
	p.a = 1 - (dot_product(&d->current_rayon, &cylinder->axis) * dot_product(&d->current_rayon, &cylinder->axis));
	p.b = 2 * (dot_product(&i.object_rayon, &d->current_rayon) - (dot_product(&d->current_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)));
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (dot_product(&i.object_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)) - (cylinder->radius * cylinder->radius);
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
//	poly_2nd_degree(d, &p, &i, cylinder);
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
		cylinder->node = v_v_add(&d->current_origin, &i.tmp_node);

		p.tmp1 = (dot_product(&d->current_rayon, &cylinder->axis) * d->solution) + dot_product(&i.object_rayon, &cylinder->axis);
		if (p.tmp1 > cylinder->lenght_max || p.tmp1 < 0)
			return (0);
		i.tmp_node_normal1 = v_v_subs(&cylinder->node, &cylinder->center);
		i.tmp_node_normal2 = v_double_mult(&cylinder->axis, p.tmp1);
		cylinder->node_normal = v_v_subs(&i.tmp_node_normal1, &i.tmp_node_normal2);
		cylinder->node_normal = normalize(&cylinder->node_normal);
	}
		return (1);
}

void 	blocked_by_a_cylinder(t_datas *d, int *light_blocked, t_object *object)
{
	t_cylinder	*tmp_cylinder;

	tmp_cylinder = object->start_cylinder;
	while (tmp_cylinder)
	{
		if (tmp_cylinder->id != d->id_cylinder)
		{
			if (cylinder_intersection(d, tmp_cylinder))
			{
				if (d->solution < d->distance_light_object)
				{
					*light_blocked = 1;
					break;
				}
			}
		}
		tmp_cylinder = tmp_cylinder->next;
	}
}
