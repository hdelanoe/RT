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

void		inputs(int keycode, t_env *e)
{
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
}

void		reset_mov_rotate(t_env *e)
{
	e->move_x = 0;
	e->move_y = 0;
	e->move_z = 0;
	e->rotate_x = 0;
	e->rotate_y = 0;
	e->rotate_z = 0;
}

int			key_functions(int keycode, t_env *e)
{
	if (keycode == 53)
		proper_exit(e);
	if (keycode == 2 || keycode == 0 || keycode == 12 || keycode == 14 ||
	keycode == 13 || keycode == 1 || keycode == 126 || keycode == 123 ||
	keycode == 125 || keycode == 124 || keycode == 6 || keycode == 7 ||
	keycode == 49 || keycode == 15)
	{
		inputs(keycode, e);
		if (keycode == 49)
			e->pixelize = e->pixelize == 1 ? 0 : 1;
		if (keycode == 15)
			e->aa_flag = e->aa_flag == 1 ? 0 : 1;
		ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
		camera_transformation(e);
		if (e->aa_flag == 1 && e->pixelize == 0)
			aa_tracer(e, 1);
		else if (e->pixelize == 1)
			pxl_tracer(e, 13);
		else
			ray_tracer(e);
		mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr,
		0, 0);
	}
	reset_mov_rotate(e);
	return (0);
}