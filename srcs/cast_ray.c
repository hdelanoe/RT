/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:52:33 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/10 11:52:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 	init_rayon_values(t_env *e, t_vector rayon, t_vector origin)
{
	e->current_rayon = rayon;
	e->current_origin = origin;
	e->ambient = 0;
	e->intersect = 0;
	e->reflect = 0;
	e->refract = 0;
//	e->bump = 0;
	e->distance = 50000;
}

int	cast_ray(t_env *e, t_vector rayon, t_vector origin)
{
	t_object 	tmp_object;

	e->skybox = 0;
	init_rayon_values(e, rayon, origin);
	tmp_object = *e->object;
	while(1)
	{
		check_intersection(e, &tmp_object);
		if (tmp_object.next == NULL)
			break ;
		tmp_object = *tmp_object.next;
	}
	if (e->intersect)
	{
		// if (e->bump)
		// {
		// 	e->current_node = bump_normal(e, e->current_node);
		// 	e->current_node_normal = bump_normal(e, e->current_node_normal);
		// }
		return (1);
	}
	return (0);
}
	

int cast_reflect_ray(t_env *e, t_rayon incident)
{
	t_rayon		reflect;
	t_physics	pl;

	pl.cos1 = 2.0 * dot_product(&incident.rayon, &incident.normal);
	reflect.rayon = v_double_mult(&incident.normal, pl.cos1);
	reflect.rayon = v_v_subs(&incident.rayon, &reflect.rayon);
	 	pl.tmp1 = v_double_mult(&reflect.rayon, 0.01);
	 reflect.origin = v_v_add(&incident.node, &pl.tmp1);
	 normalize(&reflect.rayon);
	 if(cast_ray(e, reflect.rayon, reflect.origin))
	 	return (1);
	 return(0);
}

int cast_refract_ray(t_env *e, t_rayon origin)
{
	t_rayon		refract;
	t_physics	pl;

	pl.ior = e->indice / e->object_indice;
 	pl.cos1 = dot_product(&origin.normal, &origin.rayon);
 	
 	if (pl.cos1 < 0)
 		pl.cos1 = -pl.cos1;
 	else 
 	{
 		origin.normal = v_double_mult(&origin.normal, (-1.00));
 		pl.ior = e->object_indice / e->indice;
 	}
	pl.cos2 = 1 - (pl.ior * pl.ior) * (1 - (pl.cos1 * pl.cos1)); 
	if (pl.cos2 < 0)
		return (0);
    pl.teta = pl.ior * pl.cos1 - sqrt(pl.cos2); 
 	pl.tmp1 = v_double_mult(&origin.normal, pl.teta);
 	pl.tmp2 = v_double_mult(&origin.rayon, pl.ior);
 	refract.rayon = v_v_add(&pl.tmp1, &pl.tmp2);
	pl.tmp1 = v_double_mult(&refract.rayon, 0.01);
 	refract.origin = v_v_add(&origin.node, &pl.tmp1);
 	if (cast_ray(e, refract.rayon, refract.origin))
 		return (1);
 	return (0);

}