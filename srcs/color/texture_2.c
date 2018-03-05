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

#include "rt.h"

t_color		normalize_color(t_color *color)
{
	t_color new;

	new.r = color->r / 255;
	new.g = color->g / 255;
	new.b = color->b / 255;
	return (new);
}

t_color		wrap_obj(t_env *e, t_object *object, t_object *parent)
{
	if (!object->texture)
		return (object->color);
	apply_texture(e, object);
	if (!(ft_strcmp("quad", object->type)))
		return (wrap_plane(e, object));
	else if (!(ft_strcmp("plane", object->type)))
		return (wrap_sphere(e, object));
	else if (!(ft_strcmp("sphere", object->type)))
		return (wrap_sphere(e, object));
	else if (!(ft_strcmp("cone", object->type)))
		return (wrap_cone(e, object));
	else if (!(ft_strcmp("cylinder", object->type)))
		return (wrap_cylinder(e, object));
	else if (!ft_strcmp("disk", object->type) && parent)
	{
		if (!(ft_strcmp("cylinder", parent->type)))
			return (wrap_cylinder(e, parent));
		else if (!(ft_strcmp("cone", parent->type)))
			return (wrap_cone(e, parent));
	}
	else 
		return (wrap_damier(e, object));
	return (object->color);
}

t_color		get_texture_info(unsigned char *text_data, t_env *e, int sl)
{
	int			nb;
	t_color		clr;

	nb = (e->j * 4) + (e->i * sl * 4);
	clr.b = text_data[nb];
	clr.g = text_data[nb + 1];
	clr.r = text_data[nb + 2];
	clr = normalize_color(&clr);
	return (clr);
}

void		apply_texture2(t_env *e, t_object *object)
{
	if (object->texture == 9)
		e->ti = 14;
	else if (object->texture == 10)
		e->ti = 15;
	else if (object->texture == 11)
		e->ti = 16;
	else if (object->texture == 12)
		e->ti = 17;
	else if (object->texture == 13)
		e->ti = 18;
	else if (object->texture == 14)
		e->ti = 19;
	else if (object->texture == 15)
		e->ti = 20;
	else if (object->texture == 16)
		e->ti = 21;
	else if (object->texture == 17)
		e->ti = 1;
}

void		apply_texture(t_env *e, t_object *object)
{
	if (object->texture == 1)
		e->ti = 10;
	else if (object->texture == 2)
		e->ti = 8;
	else if (object->texture == 3)
		e->ti = 11;
	else if (object->texture == 4)
		e->ti = 12;
	else if (object->texture == 5)
		e->ti = 13;
	else if (object->texture == 6)
		e->ti = 0;
	else if (object->texture == 7)
		e->ti = 7;
	else if (object->texture == 8)
		e->ti = 6;
	else
		apply_texture2(e, object);
}
