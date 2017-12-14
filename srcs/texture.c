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


// Pas encore incorpore dans le Makefile ni dans le projet dans son ensemble //

void		wrap_sphere(t_tex *tex)
{
	t_v			vp;
	t_v			d;
	double		phi;
	double		theta;

	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	all->normal = vector_sub(&all->o_tmp->pos, &all->hit);
	all->normal = vector_div_scal(&all->normal, all->o_tmp->r);
	all->lght->ray.dir = vector_sub(&all->lght->ray.pos, &all->hit);
	all->lght->ray.dir = vector_normalize(&all->lght->ray.dir);
	d = vector_mult_scal(&all->lght->ray.dir, (-1.0));
	all->angle = dot_product(&d, &all->normal);
	vp = vector_sub(&all->hit, &all->o_tmp->pos);
	vp = vector_normalize(&vp);
	phi = acos(-dot_product(&all->vecdiry, &vp));
	all->v = phi / PI;
	theta = (acos(dot_product(&vp, &all->vecdirx) / sin(phi))) / (2.0 * PI);
	t_v cross = cross_product(&all->vecdiry, &all->vecdirx);
	if (dot_product(&cross, &vp) > 0.0)
		all->u = theta;
	else
		all->u = 1.0 - theta;
}
