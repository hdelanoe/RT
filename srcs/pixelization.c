/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
//antialiasing
void	draw(t_datas *d, t_mlx *mlx, t_object *object)
{
	double		x;
	double		y;
	double		x1;
	double		y1;
	double		ns;
	double		xx;
	double		yy;
	A

	ns = 1;
	t_color		tmpclr;
	t_vector	viewplan_point;
	d->camera.origin = set_vector(0, 0, -(double)WIN_X);
	y = 0;
	y1 = (double)WIN_Y / 2;
	while (y < WIN_Y)
	{
		x = 0;
		x1 = -(double)WIN_X / 2;
		while (x < WIN_X)
		{
			tmpclr = set_color(0, 0, 0);
			d->color_finale = set_color(0, 0, 0);
			d->distance = 100000;
			yy = 0;
			while (yy < ns)
			{
				xx = 0;
				while (xx < ns)
				{
					viewplan_point = set_vector(x1 + xx, y1 - yy, 0);
					d->camera.rayon = v_v_subs(&viewplan_point, &d->camera.origin);
					d->camera.rayon = normalize(&d->camera.rayon);
					get_intersection(d, mlx, x, y, object);
					tmpclr.r += d->color_finale.r;
					tmpclr.g += d->color_finale.g;
					tmpclr.b += d->color_finale.b;
					xx += 0.20;
				}
				yy += 0.20;
			}
			tmpclr.r /= 25;
			tmpclr.g /= 25;
			tmpclr.b /= 25;
			print_color(&tmpclr, mlx, x, y);
			x++;
			x1++;
		}
		y++;
		y1--;
	}
}

//antialiasing
void		pxl_raytracing(t_all *all)
{
	int			x1;
	int			y1;
	int			tmpx;
	int			tmpy;

	all->y = 0;
	init_lst(all);
	y1 = (HEIGHT / 2);
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 200000;
			all->ray = init_ray(all, x1, y1);
			cast_smo();
			tmpy = all->y;
			tmpx = all->x;
			while (all->y < tmpy + pxlnbr)
			{
				if (all->x != tmpx)
				{
					all->x -= pxlnbr;
					x1 -= pxlnbr;
				}
				while (all->x < tmpx + pxlnbr)
				{
					if (all->x > 0 && all->x < WIDTH && all->y < HEIGHT && all->y > 0)
						pixel_puts(&all->clr, all);
					all->x++;
					x1++;
				}
				all->y++;
			}
			all->y = tmpy;
			all->o_tmp = all->head;
		}
		all->y += pxlnbr;
		// y1 -= pxlnbr;
	}
}