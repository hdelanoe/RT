/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelizatoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:07:13 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void		pxl_loop(t_all *all, int pxlnbr)
// {
// 	while (all->y < tmpy + pxlnbr)
// 	{
// 		if (all->x != tmpx)
// 		{
// 			all->x -= pxlnbr;
// 			x1 -= pxlnbr;
// 		}
// 		while (all->x < tmpx + pxlnbr)
// 		{
// 			if (all->x > 0 && all->x < WIDTH && all->y < HEIGHT && all->y > 0)
// 				pixel_puts(&all->clr, all);
// 			all->x++;
// 			x1++;
// 		}
// 		all->y++;
// 	}
// }

void		pxl_raytracing(t_all *all, int pxlnbr)
{
	int			x1;
	int			y1;
	int			tmpx;
	int			tmpy;

	all->y = 0;
	y1 = (HEIGHT / 2);
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 200000;
			all->ray = init_ray(all, x1, y1);
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
		y1 -= pxlnbr;
	}
}