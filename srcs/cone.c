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
	t_json		*tmp;

	while (json->member)
	{
		ft_putendl(json->member->name);
		cone = (t_cone*)ft_memalloc(sizeof(t_cone));
		tmp = json->member->member;
		ft_putendl(tmp->name);
		cone->vertex = set_vector(ft_atod(tmp->member->content), ft_atod(tmp->member->next->content), ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;	
		ft_putendl(tmp->name);
		cone->tangent = ft_atod(tmp->content);
		tmp = tmp->next;
		cone->lenght_max = ft_atod(tmp->content);
		tmp = tmp->next;
		cone->axis = set_vector(ft_atod(tmp->member->content), ft_atod(tmp->member->next->content), ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;
		cone->color = set_color(ft_atod(tmp->member->content), ft_atod(tmp->member->next->content), ft_atod(tmp->member->next->next->content));
		tmp = tmp->next;
		ft_putendl(tmp->name);
		cone->id = ft_atoi(tmp->content);
		cone = add_new_cone(object, cone);
		ft_putendl("XD");
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
	if (!(poly_2nd_degree(&d, &p)))
		return (0);
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