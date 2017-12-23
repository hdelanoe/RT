/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			key_functions(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 34)
		e->move_x = 25;
	else if (keycode == 32)
		e->move_x = -25;
	else if (keycode == 38)
		e->move_y = 25;
	else if (keycode == 40)
		e->move_y = -25;
	else if (keycode == 45)
		e->move_z = 25;
	else if (keycode == 46)
		e->move_z = -25;
	else if (keycode == 12)
		e->rotate_x = 1.5;
	else if (keycode == 13)
		e->rotate_x = -1.5;
	else if (keycode == 0)
		e->rotate_y = 1.5;
	else if (keycode == 1)
		e->rotate_y = -1.5;
	else if (keycode == 6)
		e->rotate_z = 1.5;
	else if (keycode == 7)
		e->rotate_z = -1.5;
	ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
	camera_transformation(e);
	ray_tracer(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
	e->move_x = 0;
	e->move_y = 0;
	e->move_z = 0;
	e->rotate_x = 0;
	e->rotate_y = 0;
	e->rotate_z = 0;
	return (0);
}