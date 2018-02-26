/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:13:40 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 14:31:39 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	v_v_subs(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = a->x - b->x;
	r.y = a->y - b->y;
	r.z = a->z - b->z;
	return (r);
}

t_vector	v_v_mult(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = (a->y * b->z) - (a->z * b->y);
	r.y = (a->z * b->x) - (a->x * b->z);
	r.z = (a->x * b->y) - (a->y * b->x);
	return (r);
}

t_vector	v_double_add(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x + b;
	r.y = a->y + b;
	r.z = a->z + b;
	return (r);
}

t_vector	v_double_subs(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x - b;
	r.y = a->y - b;
	r.z = a->z - b;
	return (r);
}

t_vector	v_double_mult(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x * b;
	r.y = a->y * b;
	r.z = a->z * b;
	return (r);
}
