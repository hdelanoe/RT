/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:23 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/21 15:35:24 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		quad_intersection(t_env *e, t_object *quad)
{
	t_object	triangle;

	triangle.point = quad->point;
	triangle.point_2 = quad->point_2;
	triangle.point_3 = quad->point_4;
	if (triangle_intersection(e, quad, &triangle))
		return (1);
	triangle.point = quad->point_3;
	triangle.point_2 = quad->point_4;
	triangle.point_3 = quad->point_2;
	if (triangle_intersection(e, quad, &triangle))
		return (1);
	return (0);
}
