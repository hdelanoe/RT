/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_blocked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_if_light_is_blocked(t_datas *d, int *light_blocked, t_object *object)
{
	*light_blocked = 0;
	blocked_by_a_sphere(d, light_blocked, object);
	if (*light_blocked == 0)
		blocked_by_a_cylinder(d, light_blocked, object);
	if (*light_blocked == 0)
		blocked_by_a_cone(d, light_blocked, object);
	if (*light_blocked == 0)
		blocked_by_a_plane(d, light_blocked, object);
	return (*light_blocked);
}
