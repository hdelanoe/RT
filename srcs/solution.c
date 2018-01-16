/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:47:58 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/14 13:53:53 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	sphere_solution(t_env *e, t_object *sphere, t_poly p)
{
	if (p.discriminant < 0)
		return (0);
	if (p.discriminant == 0)
		e->solution = - p.b;
	else
	{
		p.discriminant = sqrt(p.discriminant);
		p.s1 = (- p.b + p.discriminant);
		p.s2 = (- p.b - p.discriminant);
		e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
	}
	if (e->solution < 0)
		return (0);
	p.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	sphere->node = v_v_add(&e->current_origin, &p.tmp_node);
	sphere->node_normal = v_v_subs(&sphere->node, &sphere->center);
	sphere->node_normal = normalize(&sphere->node_normal);
	return (1);
}

int	solve_solution(t_env *e, t_poly *p)
{
	if ((*p).discriminant < 0)
		return (0);
	if ((*p).discriminant == 0)
		e->solution = - ((*p).b / (2 * (*p).a));
	else
	{
		(*p).discriminant = sqrt((*p).discriminant);
		(*p).s1 = (- (*p).b + (*p).discriminant) / (2 * (*p).a);
		(*p).s2 = (- (*p).b - (*p).discriminant) / (2 * (*p).a);
		e->solution = ((*p).s1 < (*p).s2) ? (*p).s1 : (*p).s2;
		if ((*p).s1 < (*p).s2)
        {
            (*p).tmp4 = (*p).s1;
            (*p).s1 = (*p).s2;
            (*p).s2 = (*p).tmp4;
            e->solution = (*p).s1;
        }
	}
	if (e->solution < 0)
		return (0);
	return(1);
}

int	cylinder_solution(t_env *e, t_object *cylinder, t_poly p)
{
	if (!solve_solution(e, &p))
		return (0);
	p.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	cylinder->node = v_v_add(&e->current_origin, &p.tmp_node);
	p.tmp1 = (dot_product(&e->current_rayon, &cylinder->axis) * e->solution) + dot_product(&p.object_rayon, &cylinder->axis);
	if (p.tmp1 > (cylinder->lenght_max / 2) || p.tmp1 < -(cylinder->lenght_max / 2))
		return (0);
	p.tmp_node_normal1 = v_v_subs(&cylinder->node, &cylinder->center);
	p.tmp_node_normal2 = v_double_mult(&cylinder->axis, p.tmp1);
	cylinder->node_normal = v_v_subs(&p.tmp_node_normal1, &p.tmp_node_normal2);
	cylinder->node_normal = normalize(&cylinder->node_normal);
	return (1);
}

int	cone_solution(t_env *e, t_object *cone, t_poly p)
{
	if (!solve_solution(e, &p))
		return (0);
	p.tmp_node = v_double_mult(&e->current_rayon, e->solution);
	cone->node = v_v_add(&e->current_origin, &p.tmp_node);

	p.len = (p.tmp2 * e->solution) + p.tmp3;
	if (p.len > cone->lenght_max || p.len < cone->radius)
		return (0);
	
	p.tmp_node_normal1 = v_v_subs(&cone->node, &cone->vertex);
	p.tmp_node_normal2 = v_double_mult(&cone->axis, p.len);
	p.tmp_node_normal2 = v_double_mult(&p.tmp_node_normal2, p.tmp1);
	cone->node_normal = v_v_subs(&p.tmp_node_normal1, &p.tmp_node_normal2);
	cone->node_normal = normalize(&cone->node_normal);
	return (1);
}
