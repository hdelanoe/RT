/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:55:19 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			proper_exit(t_env *e)
{
	mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int			key_functions(int keycode, t_env *e)
{
	if (keycode == 53)
		proper_exit(e);
	if (keycode == 2)
		e->move_x = 25;
	if (keycode == 0)
		e->move_x = -25;
	if (keycode == 12)
		e->move_y = 25;
	if (keycode == 14)
		e->move_y = -25;
	if (keycode == 13)
		e->move_z = 25;
	if (keycode == 1)
		e->move_z = -25;
	if (keycode == 126)
		e->rotate_x = 1.5;
	if (keycode == 125)
		e->rotate_x = -1.5;
	if (keycode == 123)
		e->rotate_y = 1.5;
	if (keycode == 124)
		e->rotate_y = -1.5;
	if (keycode == 6)
		e->rotate_z = 1.5;
	if (keycode == 7)
		e->rotate_z = -1.5;
	if (keycode == 49)
		e->pixelize = e->pixelize == 1 ? 0 : 1;
	ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
	camera_transformation(e);
	if (e->pixelize == 0)
		ray_tracer(e);
	else
		pxl_tracer(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
	e->move_x = 0;
	e->move_y = 0;
	e->move_z = 0;
	e->rotate_x = 0;
	e->rotate_y = 0;
	e->rotate_z = 0;
	return (0);
}
