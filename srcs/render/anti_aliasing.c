/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_loading_bar(t_env *e, int i)
{
	int x;
	int y;

	x = e->width / 4 + 10 + (i * 60);
	y = e->height / 3 + 25;
	if (e->loading == 1)
		return ;
	if (e->sonic % 2 == 0)
		mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->sonic_d, 50, e->height - 250);
	else
		mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->sonic_u, 50, e->height - 250);
	e->sonic++;
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->barre_bat, x, y);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->barre_bat, x + 10, y);
	mlx_do_sync(e->mlx.mlx_ptr);
}

void	anti_aliasing_clr_merge(t_color *anti, t_color *clr)
{
	anti->r += clr->r;
	anti->g += clr->g;
	anti->b += clr->b;
}

void	antialias_loop_init(t_grid *aa, t_env *e, int sample)
{
	aa->y = aa->yy;
	while (aa->y < sample + aa->yy)
	{
		aa->x = aa->xx;
		while (aa->x < sample + aa->xx)
		{
			aa->ctmp = vp_init(e, e->camera, e->viewplane_point_up_left, *aa);
			anti_aliasing_clr_merge(&aa->color, &aa->ctmp);
			aa->x += 0.25;
		}
		aa->y += 0.25;
	}
}

void	*aa_tracer_void(void *e)
{
	aa_tracer(e, 1);
	return (NULL);
}

void	aa_tracer(t_env *e, int sample)
{
	t_grid	aa;

	aa.filter = set_color(0, 0, 0);
	aa.yy = e->begin;
	while (aa.yy < e->fin)
	{
		aa.xx = 0;
		while (aa.xx < e->width)
		{
			aa.color = set_color(0, 0, 0);
			antialias_loop_init(&aa, e, sample);
			aa.color = c_double_div(&aa.color, 16);
			aa.color = set_filter(e, aa.color);
			print_color(&aa.color, e, aa.x, aa.y);
			aa.xx++;
		}
		aa.yy++;
	}
}
