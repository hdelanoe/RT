/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:14:49 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 14:31:54 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	v_double_div(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x / b;
	r.y = a->y / b;
	r.z = a->z / b;
	return (r);
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}
