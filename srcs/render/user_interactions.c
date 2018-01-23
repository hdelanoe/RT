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

void    inputs2(int keycode, t_env *e) 
{ 
  	if (keycode == 17) 
    	e->am_flag = e->am_flag == 1 ? 0 : 1;
	else if (keycode == 35)
    	e->stereo_flag = e->stereo_flag == 1 ? 0 : 1;
    else if (keycode == 82) 
    	e->filter_flag = 0;
    else if (keycode == 83) 
    	e->filter_flag = 1;
    else if (keycode == 84) 
    	e->filter_flag = 2;
    else if (keycode == 85) 
    	e->filter_flag = 3;
    else if (keycode == 86) 
    	e->filter_flag = 4;
    else if (keycode == 87) 
    	e->filter_flag = 5;
    else if (keycode == 88) 
    	e->filter_flag = 6;
    else if (keycode == 36)
    	e->edit_flag = e->edit_flag == 1 ? 0 : 1; 

} 

void		inputs(int keycode, t_env *e)
{
	if (keycode == 2)
		e->move_x = 25;
	else if (keycode == 0)
		e->move_x = -25;
	else if (keycode == 12)
		e->move_y = 25;
	else if (keycode == 14)
		e->move_y = -25;
	else if (keycode == 13)
		e->move_z = 25;
	else if (keycode == 1)
		e->move_z = -25;
	else if (keycode == 126)
		e->rotate_x = 1.5;
	else if (keycode == 125)
		e->rotate_x = -1.5;
	else if (keycode == 123)
		e->rotate_y = 1.5;
	else if (keycode == 124)
		e->rotate_y = -1.5;
	else if (keycode == 6)
		e->rotate_z = 1.5;
	else if (keycode == 7)
		e->rotate_z = -1.5;
	inputs2(keycode, e);
}

void		print_info(t_env *e)
{
	if (e->edit_flag)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 80,
		0xFFFFFF, "Edit mode : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 80,
		0xFFFFFF, "Edit mode : OFF");
	if (e->pixelize)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 100,
		0xFFFFFF, "Pixelization : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 100,
		0xFFFFFF, "Pixelization : OFF");
	if (e->aa_flag)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 120,
		0xFFFFFF, "Anti-Aliasing : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 120,
		0xFFFFFF, "Anti-Aliasing : OFF");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 900,
	0xFFFFFF, "Radius = ");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 95, 900,
	0xFFFFFF, ft_itoa(e->tmp_rad));
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
	keycode == 49 || keycode == 15 || keycode == 17 || keycode == 35 ||
	keycode == 82 || keycode == 83 || keycode == 84 || keycode == 85 ||
	keycode == 86 || keycode == 87 || keycode == 88 || keycode == 36 ||
	keycode == 4 || keycode == 69 || keycode == 78)
	{
		inputs(keycode, e);
		if (keycode == 69)
			e->tmp_rad += 1;
		if (keycode == 78)
			e->tmp_rad -= 1;
		if (keycode == 49)
			e->pixelize = e->pixelize == 1 ? 0 : 1;
		if (keycode == 15)
			e->aa_flag = e->aa_flag == 1 ? 0 : 1;
		if (keycode == 4)
			e->hide = e->hide == 0 ? 1 : 0;
		ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
		camera_transformation(e);
		// if (!((e->mlx.img_ptr = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
		// "./textures/thewood.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		// 	ft_kill("Texture error");
		// e->mlx.data = (unsigned char*)mlx_get_data_addr(e->mlx.img_ptr,
		// &e->mlx.bpp, &e->mlx.l_size, &e->mlx.endian);
//		reset_stereo(e);
	//	e->viewplane_point_up_left = viewplane_transformation(e->camera);
	//	camera_transformation(e, &e->lstereo);
	//	e->lviewplane = viewplane_transformation(e->lstereo);
	//	camera_transformation(e, &e->rstereo);
	//	e->rviewplane = viewplane_transformation(e->rstereo);
		if (e->aa_flag == 1 && e->pixelize == 0)
			aa_tracer(e, 1);
		else if (e->pixelize == 1)
		{
			if (e->edit_flag)
				pxl_edit_tracer(e, 13);
			else
				pxl_tracer(e, 13);
		}
		else if (e->edit_flag == 1)
			edit_tracer(e);
	//	else if (e->stereo_flag == 1)
	//		stereo_tracer(e);
		else
			ray_tracer(e);
		mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
		if (e->hide)
			print_info(e);
	}
	reset_mov_rotate(e);
	// printf("key %d\n", keycode);
	return (0);
}
