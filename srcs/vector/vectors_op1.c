/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/05 14:33:14 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	set_vector(double x, double y, double z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double		magnitude(t_vector *a)
{
	return (sqrtf(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_vector	normalize(t_vector *a)
{
	t_vector	na;
	double		magn;

	magn = magnitude(a);
	na.x = a->x / magn;
	na.y = a->y / magn;
	na.z = a->z / magn;
	return (na);
}

double		dot_product(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vector	v_v_add(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = a->x + b->x;
	r.y = a->y + b->y;
	r.z = a->z + b->z;
	return (r);
}
