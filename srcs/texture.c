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
	t_vector		vp;
	t_vector		d;
	double			phi;
	double			theta;

	all->hit = v_double_mult(&all->ray.dir, all->t);
	all->hit = v_v_add(&all->ray.pos, &all->hit);
	all->normal = v_v_subs(&all->o_tmp->pos, &all->hit);
	all->normal = v_double_div(&all->normal, all->o_tmp->r);
	all->lght->ray.dir = v_v_subs(&all->lght->ray.pos, &all->hit);
	all->lght->ray.dir = normalize(&all->lght->ray.dir);
	d = v_double_mult(&all->lght->ray.dir, (-1.0));
	all->angle = dot_product(&d, &all->normal);
	vp = v_v_subs(&all->hit, &all->o_tmp->pos);
	vp = normalize(&vp);
	phi = acos(-dot_product(&all->vecdiry, &vp));
	all->v = phi / PI;
	theta = (acos(dot_product(&vp, &all->vecdirx) / sin(phi))) / (2.0 * PI);
	t_vector cross = v_v_mult(&all->vecdiry, &all->vecdirx);
	if (dot_product(&cross, &vp) > 0.0)
		all->u = theta;
	else
		all->u = 1.0 - theta;
}

t_color		get_texture_info(char *tex, t_all *all, int i)
{
	int			nb;
	t_color		clr;

	/* test fail du degrade de noir selon l'angle du rayon sur le point touche sur a sphere
	if (all->angle <= 0 && i == 1)
		return (create_color(0, 0, 0, 0)); */
	if (i == 1) // sphere
		nb = (all->j * 4) + (all->i * all->i_sl * 4);
	else // plan
		nb = (all->x * 4) + (all->y * all->i_sl2 * 4);
	clr.b = tex[nb];
	clr.g = tex[nb + 1];
	clr.r = tex[nb + 2];
	return (clr);
}
