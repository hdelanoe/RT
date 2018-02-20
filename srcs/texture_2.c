/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:07:13 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			normalize_color(t_color *color)
{
	t_color new;

	new.r = color->r / 255;
	new.g = color->g / 255;
	new.b = color->b / 255;
	return (new);
}

void			wrap_obj(t_env *e, t_object *object, t_object *parent)
{
	if (!(ft_strcmp("plane", object->type)))
		wrap_plane(e);
	if (!(ft_strcmp("sphere", object->type)))
		wrap_sphere(e, object);
	if (!(ft_strcmp("cylinder", object->type)))
		wrap_cylinder(e, object);
	if (!ft_strcmp("disk", object->type))
		if (!(ft_strcmp("cylinder", parent->type)))
			wrap_cylinder(e, parent);
}
