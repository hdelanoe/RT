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

#include "rt.h"

void		create_paraboloid(t_env *e, t_json *json)
{
	t_object	*paraboloid;
	t_json		*tmp;

	paraboloid = init_material();
	if (!(paraboloid->type = ft_strdup("paraboloid")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		paraboloid_attribut(paraboloid, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	add_new_object(&e->object, paraboloid);
}

void		paraboloid_attribut(t_object *object, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		object->center = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		object->axis = parse_normal(tmp->member);
	else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
		object->lenght_max = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		object->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, object);
	else
		ft_printf("{R}WARNING:{E} paraboloid as a bad attribut\n");
}

int			paraboloid_intersection(t_env *e, t_object *para)
{
	t_poly	p;

	p.object_rayon = v_v_subs(&e->current_origin, &para->center);
	p.a = 1 - (dot_product(&e->current_rayon, &para->axis) *
		dot_product(&e->current_rayon, &para->axis));
	p.b = 2 * (dot_product(&p.object_rayon, &e->current_rayon) -
		(dot_product(&e->current_rayon, &para->axis) *
		(dot_product(&p.object_rayon, &para->axis) + 2 * para->lenght_max)));
	p.c = dot_product(&p.object_rayon, &p.object_rayon) -
		(dot_product(&p.object_rayon, &para->axis) *
		(dot_product(&p.object_rayon, &para->axis) + 4 * para->lenght_max));
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	return (paraboloid_solution(e, para, p));
}

int			paraboloid_solution(t_env *e, t_object *para, t_poly p)
{
	if (!solve_solution(e, &p))
		return (0);
	p.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	para->node = v_v_add(&e->current_origin, &p.tmp_node);
	p.tmp1 = (dot_product(&e->current_rayon, &para->axis) * e->solution)
	+ dot_product(&p.object_rayon, &para->axis);
	p.tmp_node_normal1 = v_v_subs(&para->node, &para->center);
	p.tmp_node_normal2 = v_double_mult(&para->axis,
		(p.tmp1 + para->lenght_max));
	para->node_normal = v_v_subs(&p.tmp_node_normal1, &p.tmp_node_normal2);
	para->node_normal = normalize(&para->node_normal);
	return (1);
}
