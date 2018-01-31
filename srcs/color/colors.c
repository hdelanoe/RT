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

double get_specular(t_light *light, t_vector *view, t_vector *node)
{
	t_vector	tmp;
	t_vector	r;
	double 		reflect;
	double 		phong_color;

	reflect =  dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);

	phong_color = 0.2 * powf(dot_product(view, &r), 50) * 3;

	return (phong_color);
}

void init_ray_values(t_rayon *ray, t_env *e)
{
	ray->origin = e->current_origin;
	ray->rayon = e->current_rayon;
	ray->node = e->current_node;
	ray->normal = e->current_node_normal;
}

void	shoot_new_color(t_env *e, t_color *c, double coef)
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
	// e->recursion--;
}

void	recurse_color(t_env *e, t_rayon ray, t_color *c)
{
	while (--(e->recursion) > 0)
	{

		if (e->reflect)
		{
			if (cast_reflect_ray(e, ray))
			{
				shoot_new_color(e, c, e->diffuse);
				// continue ;
			}
		}
		else if (e->refract)
		{
			if (cast_refract_ray(e, ray))
			{
				shoot_new_color(e, c, 1 - e->absorbtion);
			//	continue ;
			}

		}
	}
}

t_color	ambient_occlusion(t_env *e)
{
	t_color c;
	t_rayon origin;
	t_rayon ray;
	t_vector tmp;
	int sample;
	int hit;


	c = set_color(1, 1, 1);
	init_ray_values(&origin, e);
	sample = 16;
	hit = 0;
	while (sample > 0)
	{
		ray.rayon.x = RANDOM;
		ray.rayon.y = RANDOM;
		ray.rayon.z = RANDOM;
		ray.rayon = v_v_add(&ray.rayon, &origin.normal);
		ray.rayon = normalize(&ray.rayon);
		tmp = v_double_mult(&ray.rayon, 0.01);
		ray.origin = v_v_add(&origin.node, &tmp);
		if (cast_ray(e, ray.rayon, ray.origin))
			hit++;
		sample--;
	}
	if (hit)
		c = c_double_mult(&c, (double)1/hit);
	return (c);
}

t_color			get_color(t_env *e)
{
	t_color		c;
	t_rayon		ray;
	t_color 	diffuse;

	double 		specular;
	t_light		*tmp_light;
	t_vector 	tmp_angle;

	init_ray_values(&ray, e);
	c = c_double_mult(&e->current_color, e->ambient);
	if (e->edit_flag)
		return (c);
	tmp_light = e->light;
	while (tmp_light)
	{
		diffuse = set_color(0, 0, 0);
		tmp_light->rayon = v_v_subs(&e->current_node, &tmp_light->origin);
		e->distance_light_object = magnitude(&tmp_light->rayon);
		tmp_light->rayon = normalize(&tmp_light->rayon);
		e->current_origin = tmp_light->origin;
		e->current_rayon = tmp_light->rayon;
		if (!light_intersection(e))
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
		tmp_light = tmp_light->next;
	}
	recurse_color(e, ray, &c);
	return (c);
}
