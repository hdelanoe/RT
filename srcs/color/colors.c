/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		choose_color(t_env *e)
{
	t_color new;

	if (e->aa_flag == 1 && e->pixelize == 0)
	{
		if (e->cel_shade == 1)
			new = e->current_color;
		else
			new = get_color(e);
	}
	else if (e->pixelize == 1)
	{
		if (e->edit_flag == 1)
			new = e->current_color;
		else if (e->cel_shade == 1)
			new = cel_shade_color(e);
		else
			new = get_color(e);
	}
	else if (e->edit_flag == 1)
		new = e->current_color;
	else if (e->cel_shade == 1)
		new = cel_shade_color(e);
	else
		new = get_color(e);
	return (new);
}

double		get_specular(t_light *light, t_vector *view, t_vector *node)
{
	t_vector	tmp;
	t_vector	r;
	double		reflect;
	double		phong_color;

	reflect = dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);
	phong_color = 0.2 * powf(dot_product(view, &r), 50) * 3;
	return (phong_color);
}

void		init_ray_values(t_rayon *ray, t_env *e)
{
	ray->origin = e->current_origin;
	ray->rayon = e->current_rayon;
	ray->node = e->current_node;
	ray->normal = e->current_node_normal;
}

void		shoot_new_color(t_env *e, t_color *c, double coef)
{
	t_color shade;
	t_color shade_sub;

	shade = get_color(e);
	shade_sub = set_color(0.5, 0.5, 0.5);
	shade = c_double_mult(&shade, coef);
	if (shade.r < 0.1 && shade.g < 0.1 && shade.b < 0.1)
		*c = c_c_subs(c, &shade_sub);
	else
		*c = c_c_add(c, &shade);
}

void		recurse_color(t_env *e, t_rayon ray, t_color *c)
{
	while (--(e->recursion) > 0)
	{
		if (e->reflect)
		{
			if (cast_reflect_ray(e, ray))
				shoot_new_color(e, c, e->diffuse);
		}
		else if (e->refract)
		{
			if (cast_refract_ray(e, ray))
				shoot_new_color(e, c, 1 - e->absorbtion);
		}
	}
}

t_color		ambient_occlusion(t_env *e)
{
	t_color		c;
	t_rayon		origin;
	t_rayon		ray;
	t_vector	tmp;
	int			sample;

	c = set_color(1, 1, 1);
	init_ray_values(&origin, e);
	sample = 16;
	e->hit = 0;
	while (sample > 0)
	{
		ray.rayon.x = RANDOM;
		ray.rayon.y = RANDOM;
		ray.rayon.z = RANDOM;
		ray.rayon = v_v_add(&ray.rayon, &origin.normal);
		ray.rayon = normalize(&ray.rayon);
		tmp = v_double_mult(&ray.rayon, 0.01);
		ray.origin = v_v_add(&origin.node, &tmp);
		e->hit = cast_ray(e, ray.rayon, ray.origin) ? e->hit + 1 : e->hit;
		sample--;
	}
	return (e->hit ? c_double_mult(&c, (double)1 / e->hit) : c);
}

void		get_area_light_origin(t_env *e, t_light *area_light, int nb)
{
	if (nb == 0)
		area_light->origin = area_light->point;
	else if (nb % 4 == 0)
	{
		area_light->origin = v_v_subs(&area_light->origin, &e->rayon_length);
		area_light->origin = v_v_add(&area_light->origin, &e->rayon_width_div);
	}
	else
		area_light->origin = v_v_add(&area_light->origin, &e->rayon_length_div);
}

t_color		get_area_light_intensity(t_env *e, t_light *area_light, t_rayon *ray, t_color *c)
{
	t_color 	diffuse;
	t_color		*a_c;
	int			i;
	int			j;
	int			nb;
	double 		specular;
	t_vector 	tmp_angle;
	t_color   	c_light;

	if(!(a_c = (t_color*)ft_memalloc(sizeof(t_color) * 16)))
		exit_rt(1);
	e->rayon_length = v_v_subs(&area_light->point_2, &area_light->point);
	e->rayon_length_div = v_double_div(&e->rayon_length, 3);
	e->rayon_width = v_v_subs(&area_light->point_4, &area_light->point);
	e->rayon_width_div = v_double_div(&e->rayon_width, 3);
	nb = 0;
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			get_area_light_origin(e, area_light, nb);
			// printf("area_light->origin: %f, %f, %f\n", area_light->origin.x, area_light->origin.y, area_light->origin.z);
			diffuse = set_color(0, 0, 0);
			area_light->rayon = v_v_subs(&e->current_node, &area_light->origin);
			e->distance_light_object = magnitude(&area_light->rayon);
			area_light->rayon = normalize(&area_light->rayon);
			e->current_origin = area_light->origin;
			e->current_rayon = area_light->rayon;
			c_light = light_intersection(e, area_light);
			if (!(c_light.r == 0 && c_light.g == 0 && c_light.b == 0))
			{
				tmp_angle = v_double_mult(&area_light->rayon, (-1));
				area_light->angle = dot_product(&e->current_node_normal, &tmp_angle);
				specular = e->specular * get_specular(area_light, &ray->rayon, &ray->normal);
				if (area_light->angle > 0)
				{
					diffuse = c_c_mult(&e->current_color, &area_light->color);
					diffuse = c_double_add(&diffuse, specular);
					diffuse = c_double_mult(&diffuse, area_light->angle);
					diffuse = c_double_mult(&diffuse, e->diffuse);
				}
				a_c[nb] = c_c_add(c, &diffuse);
			}
			else
				a_c[nb] = *c;
			nb++;
			i++;
		}
		j++;
	}
	// printf("\n");
	i = 0;
	while (i < 16)
	{
		c->r += a_c[i].r;
		c->g += a_c[i].g;
		c->b += a_c[i].b;
		i++;
	}
	*c = c_double_div(c, 16);
	free(a_c);
	return (*c);
}

t_color		get_color(t_env *e)
{	
	t_color		c;
	t_color		c_light;
	t_rayon		ray;
	t_color		diffuse;
	double		specular;
	t_light		*tmp_light;
	t_vector	tmp_angle;

	init_ray_values(&ray, e);
	c = c_double_mult(&e->current_color, e->ambient);
	if (c.r == 0 && c.g == 0 && c.b == 0 && e->intersect == 0)
		return (c);
	tmp_light = e->light;
	while (tmp_light)
	{
		if (!ft_strcmp(tmp_light->type, "area_light"))
			c = get_area_light_intensity(e, tmp_light, &ray, &c);
		else
		{
			diffuse = set_color(0, 0, 0);
			tmp_light->rayon = v_v_subs(&e->current_node, &tmp_light->origin);
			e->distance_light_object = magnitude(&tmp_light->rayon);
			tmp_light->rayon = normalize(&tmp_light->rayon);
			e->current_origin = tmp_light->origin;
			e->current_rayon = tmp_light->rayon;
			c_light = light_intersection(e, tmp_light);
			if (!(c_light.r == 0 && c_light.g == 0 && c_light.b == 0))
			{
				tmp_angle = v_double_mult(&tmp_light->rayon, (-1));
				tmp_light->angle = dot_product(&e->current_node_normal, &tmp_angle);
				specular = e->specular * get_specular(tmp_light, &ray.rayon, &ray.normal);
				if (tmp_light->angle > 0)
				{
					diffuse = c_c_mult(&e->current_color, &tmp_light->color);
					diffuse = c_double_add(&diffuse, specular);
					diffuse = c_double_mult(&diffuse, tmp_light->angle);
					diffuse = c_double_mult(&diffuse, e->diffuse);
				}
				c = c_c_add(&c, &diffuse);
			}
		}
		tmp_light = tmp_light->next;
	}
	recurse_color(e, ray, &c);
	return (c);
}
