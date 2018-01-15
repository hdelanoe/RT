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
	e->bump = 0;
	e->recursion = 1;
}

t_vector bump_normal(t_vector normal)
{
	double n;

	n = noise(normal.x, normal.y, normal.z);
	return (v_double_mult(&normal, n));
}

int	cast_ray(t_env *e, t_vector rayon, t_vector origin)
{
	t_object 	*tmp_object;

	init_rayon_values(e, rayon, origin);
//	printf("r %f g %f b %f\n", e->color_finale.r, e->color_finale.g, e->color_finale.b);
	tmp_object = e->object;
	check_intersection(e, tmp_object);
	if (e->intersect)
		return (1);
	return (0);
}
	//	if (e->bump)
	//	{
	//		node.node = bump_normal(e->current_node);
	//		node.normal = bump_normal(e->current_node_normal);
	//	}

int cast_reflect_ray(t_env *e, t_rayon incident)
{
	t_rayon		reflect;
	t_physics	pl;
	// t_vector	inv;

	pl.cos1 = 2.0 * dot_product(&incident.rayon, &incident.normal);
	reflect.rayon = v_double_mult(&incident.normal, pl.cos1);
	reflect.rayon = v_v_subs(&incident.rayon, &reflect.rayon);
	// inv = v_double_mult(&origin.rayon, (double)-1);
	// pl.cos1 = dot_product(&inv, &origin.normal);
	// if (pl.cos1 >= 0)
	// 	pl.teta = 2 * pl.cos1;
	// else
	// 	pl.teta = -2 * pl.cos1;
	// pl.tmp1 = v_double_mult(&origin.normal, pl.teta);
	// reflect.rayon = v_v_add(&origin.rayon, &pl.tmp1);
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
	t_vector	inv;


	if (e->in_out < 0)
		pl.ior = R_VOID / R_VOID;
 	else
 		pl.ior = R_VOID / R_VOID;
 	inv = v_double_mult(&origin.rayon, 1.0);
 	pl.cos1 = dot_product(&origin.normal, &inv);
 	pl.cos2 = sqrt(1 - (pl.ior * pl.ior) * (1 - (pl.cos1 * pl.cos1))); 
 	if ( pl.cos1 < 0)
 		pl.cos1 = -pl.cos1;
 	else 
 		origin.normal = v_double_mult(&origin.normal, (-1.00));
    pl.teta = pl.ior * pl.cos1 - pl.cos2; 
 	pl.tmp1 = v_double_mult(&origin.normal, pl.teta);
 	pl.tmp2 = v_double_mult(&origin.rayon, pl.ior);
 	refract.rayon = v_v_add(&pl.tmp1, &pl.tmp2);
	pl.tmp1 = v_double_mult(&refract.rayon, 0.01);
 	refract.origin = v_v_add(&origin.node, &pl.tmp1);
	normalize(&refract.rayon);
	e->in_out *= -1;
 	if (cast_ray(e, refract.rayon, refract.origin))
 		return (1);
 	return (0);

}