/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/05 15:21:55 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		ambient_occlusion(t_env *e)
{
	t_color		c;
	t_rayon		origin;
	t_rayon		ray;
	t_vector	tmp;
	int			sample;

	c = set_color(1, 1, 1);
	void init_ray_values(t_rayon *origin, t_env *e);
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

void	init_ray_values(t_rayon *ray, t_env *e)
{
 	double n;
 
    ray->origin = e->current_origin;
    ray->rayon = e->current_rayon;
    ray->node = e->current_node;
   	ray->normal = e->current_node_normal;
   if (e->bump == 1)
   {
    	n = noise(e, e->perlin.a * ray->node.x,
    		e->perlin.c  * ray->node.y, e->perlin.b * ray->node.z);
    	ray->node.y *= n;
 		ray->normal = v_double_add(&ray->normal, n);
    	ray->normal = normalize(&ray->normal);
   }
   else if (e->bump == 2)
   {
    	n = noise(e, e->perlin.a * ray->node.x,
    		e->perlin.c  * ray->node.y, e->perlin.b * ray->node.z);
      	n = e->perlin.d * sin((ray->node.y + ray->node.x)
      		* e->perlin.c + n) + e->perlin.d;
 		ray->node = v_double_mult(&ray->node, n);
 		ray->normal = v_double_add(&ray->normal, n);
    	ray->normal = normalize(&ray->normal);
   }
}

t_color		calc_diffuse(t_env *e, t_light *light, t_rayon *ray, t_color c)
{
	t_color		diffuse;
	t_vector	angle;
	double		specular;

	diffuse = set_color(0, 0, 0);
	angle = v_double_mult(&light->rayon, (-1));
	light->angle = dot_product(&ray->normal, &angle);
	specular = e->specular *
				get_specular(light, &ray->rayon, &ray->normal);
	if (light->angle > 0)
	{
		diffuse = c_c_mult(&e->current_color, &c);
		diffuse = c_double_add(&diffuse, specular);
		diffuse = c_double_mult(&diffuse, light->angle);
		diffuse = c_double_mult(&diffuse, e->diffuse);
	}
	return(diffuse);
}

t_color		add_diffuse(t_env *e, t_color *c, t_light *light, t_rayon *ray)
{
	t_color		diffuse;
	t_color		c_light;
	
	light->rayon = v_v_subs(&ray->node, &light->origin);
	e->distance_light_object = magnitude(&light->rayon);
	light->rayon = normalize(&light->rayon);
	e->current_origin = light->origin;
	e->current_rayon = light->rayon;
	c_light = light_intersection(e, light);
	c_light = c_double_mult(&c_light,
				1 - (e->distance_light_object / 50000));
	if (c_light.r == 0 && c_light.g == 0 && c_light.b == 0)
		return (*c);
	diffuse = calc_diffuse(e, light, ray, c_light);
	return (c_c_add(c, &diffuse));
}

t_color		get_color(t_env *e)
{
	t_color	c;
	t_rayon	ray;
	t_light	tmp_light;

	init_ray_values(&ray, e);
	c = c_double_mult(&e->current_color, e->ambient);
	c = c_double_mult(&c, 1 - (e->distance / 50000));
	if ((c.r == 0 && c.g == 0 && c.b == 0)
		|| e->edit_flag == 1)
		return (c);
	tmp_light = *e->light;
	while (1)
	{
		if (!ft_strcmp(tmp_light.type, "area_light"))
			c = get_area_light_intensity(e, &tmp_light, &ray, &c);
		else
			c = add_diffuse(e, &c, &tmp_light, &ray);
		if (tmp_light.next == NULL)
			break ;
		tmp_light = *tmp_light.next;
	}
	recurse_color(e, ray, &c);
	return (c);
}
