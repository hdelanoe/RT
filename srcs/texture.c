/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:07:13 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		normalize_color(t_color *color)
{
	t_color new;

	new.r = color->r / 255;
	new.g = color->g / 255;
	new.b = color->b / 255;
	// if (new.b > 1)
	// 	new.b = 1;
	// if (new.g > 1)
	// 	new.g = 1;
	// if (new.r > 1)
	// 	new.r = 1;
	// printf("%f %f %f\n", new.r, new.g, new.b);
	return (new);
}

void		load_texture(t_env *e)
{
	if (!((e->text_img = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/stars.xpm", &(e->sl), &e->bpp))))
		ft_kill("Texture error");
	e->text_data = (unsigned char*)mlx_get_data_addr(e->text_img, &e->bpp, &e->naz, &e->end);
}

void		wrap_sphere(t_env *e, t_object *object)
{
	t_vector			vp;
	double				phi;
	double				theta;
	t_vector			vecdirx;
	t_vector			vecdiry;
	t_vector			cross;

	vecdirx = (t_vector){1, 0, 0};
	vecdiry = (t_vector){0, 1, 0};
	cross = v_v_mult(&vecdiry, &vecdirx);
	vp = v_v_subs(&object->center, &e->current_node);
	vp = normalize(&vp);
	phi = acos(-dot_product(&vecdiry, &vp));
	e->v = phi / PI;
	theta = (acos(-dot_product(&vp, &vecdirx) / sin(phi))) / (2.0 * PI);
	if (dot_product(&cross, &vp) > 0.0)
		e->u = theta;
	else
		e->u = 1.0 - theta;
}

void		wrap_cylinder(t_env *e, t_object *object)
{
	t_vector			vp;
	double				phi;
	double				theta;
	t_vector			cross;
	t_vector			vecdirx;
	t_vector			vecdiry;

	vecdirx = (t_vector){1, 0, 0};
	vecdiry = (t_vector){0, 1, 0};
	cross = v_v_mult(&vecdiry, &vecdirx);
	vp = v_v_subs(&object->center, &e->current_node);
	vp = normalize(&vp);
	phi = acos(-dot_product(&vecdiry, &vp));
	e->v = phi / PI;
	theta = (acos(dot_product(&vp, &vecdirx) / sin(phi))) / (2.0 * PI);
	if (dot_product(&cross, &vp) > 0.0)
		e->u = theta;
	else
		e->u = 1.0 - theta;
}

t_color		get_texture_info(unsigned char *text_data, t_env *e)
{
	int			nb;
	t_color		clr;

	nb = (e->j * 4) + (e->i * e->sl * 4);
	clr.b = text_data[nb];
	clr.g = text_data[nb + 1];
	clr.r = text_data[nb + 2];
	// if (clr.r || clr.g)
	// printf("%f %f %f\n", clr.r, clr.g, clr.b);
	clr = normalize_color(&clr);
	return (clr);
}