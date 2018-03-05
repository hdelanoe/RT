/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:16:59 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/03/05 15:17:00 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	change_color(t_env *e, t_object *object, t_object *parent)
{
	if (object->refract == 0)
		return (set_color(0, 0, 0));
	if (object->texture != 0)
		return (wrap_obj(e, object, parent));
	return (object->color);
}
