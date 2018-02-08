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
	return (new);
}

void		load_texture3(t_env *e)
{
		if (!((e->text_img[4] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/wall.xpm", &(e->sl[4]), &e->bpp[4]))))
		ft_kill("Texture error");
	e->text_data[4] = (unsigned char*)mlx_get_data_addr(e->text_img[4], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[5] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/thewood.xpm", &(e->sl[5]), &e->bpp[5]))))
		ft_kill("Texture error");
	e->text_data[5] = (unsigned char*)mlx_get_data_addr(e->text_img[5], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[6] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/moon.xpm", &(e->sl[6]), &e->bpp[6]))))
		ft_kill("Texture error");
	e->text_data[6] = (unsigned char*)mlx_get_data_addr(e->text_img[6], &e->naz,
	&e->naz, &e->end);
}

void		load_texture2(t_env *e)
{
	if (!((e->text_img[7] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/metal.xpm", &(e->sl[7]), &e->bpp[7]))))
		ft_kill("Texture error");
	e->text_data[7] = (unsigned char*)mlx_get_data_addr(e->text_img[7], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[8] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/skyboxe.xpm", &(e->sl[8]), &e->bpp[8]))))
		ft_kill("Texture error");
	e->text_data[8] = (unsigned char*)mlx_get_data_addr(e->text_img[8], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[9] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/jean.xpm", &(e->sl[9]), &e->bpp[9]))))
		ft_kill("Texture error");
	e->text_data[9] = (unsigned char*)mlx_get_data_addr(e->text_img[9], &e->naz,
	&e->naz, &e->end);
}

void		load_texture(t_env *e)
{
	if (!((e->text_img[0] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/earth_8k.xpm", &e->sl[0], &e->bpp[0]))))
		ft_kill("Texture error");
	e->text_data[0] = (unsigned char*)mlx_get_data_addr(e->text_img[0], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[1] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/space.xpm", &(e->sl[1]), &e->bpp[1]))))
		ft_kill("Texture error");
	e->text_data[1] = (unsigned char*)mlx_get_data_addr(e->text_img[1], &e->naz,
	&e->naz, &e->end);
	if (!((e->text_img[2] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/stars.xpm", &(e->sl[2]), &e->bpp[2]))))
		ft_kill("Texture error");
	e->text_data[2] = (unsigned char*)mlx_get_data_addr(e->text_img[2], &e->naz,
	&e->naz, &e->end);
		if (!((e->text_img[3] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/wood.xpm", &(e->sl[3]), &e->bpp[3]))))
		ft_kill("Texture error");
	e->text_data[3] = (unsigned char*)mlx_get_data_addr(e->text_img[3], &e->naz,
	&e->naz, &e->end);
	load_texture2(e);
	load_texture3(e);
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
	e->i = (int)(e->v * (e->bpp[1 + (e->ti % 9)]));
	e->j = (int)(e->u * e->sl[1 + (e->ti % 9)]);
	e->current_color = get_texture_info(e->text_data[1 + (e->ti % 9)], e, e->sl[1 + (e->ti % 9)]);
}

void		wrap_plane(t_env *e)//, t_object *object)
{
	int carre;

	// if (!ft_strcmp(object->tex_type, "square"))
		carre = floor(e->current_node.x) + floor(e->current_node.z);
	// else if (!ft_strcmp(object->tex_type, "columns"))
		// carre = floor(e->current_node.x);
	// else if (!ft_strcmp(object->tex_type, "lines"))
		// carre = floor(e->current_node.z);
	if (carre % 2 == 0)
		e->current_color = set_color(0, 0, 0);
	else
		e->current_color = set_color(0.6184, 0.54561, 0.3481);
}

void		wrap_cone(t_env *e, t_object *object)
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
	e->i = (int)(e->v * e->bpp[1 + (e->ti % 9)]);
	e->j = (int)(e->u * e->sl[1 + (e->ti % 9)]);
	e->current_color = get_texture_info(e->text_data[1 + (e->ti % 9)], e, e->sl[1 + (e->ti % 9)]);
}

t_vector	v_v_mlt(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = a->x * b->x;
	r.y = a->y * b->y;
	r.z = a->z * b->z;
	return (r);
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}

void		wrap_cylinder(t_env *e, t_object *object)
{
	t_vector	d;

	d = v_v_subs( &object->center, &e->current_node);
	d = normalize(&d);
	e->u = atan2(d.x, d.z) / (2 * PI) + 0.5;
	e->v = d.y * 0.5 + 0.5;
	e->i = max((e->u * e->bpp[0 + (e->ti % 9)]), 0);
	e->j = max((e->v * e->sl[0 + (e->ti % 9)]), 0);
	e->current_color = get_texture_info(e->text_data[0 + (e->ti % 9)], e, e->sl[0 + (e->ti % 9)]);
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
