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

void		choose_display_mode(t_env *e)
{
	if (e->aa_flag == 1 && e->pixelize == 0 && !e->edit_flag)
		aa_tracer(e, 1);
	if (e->pixelize == 1)
		pxl_tracer(e, 13);
	else if ((e->render_mode == 2 || e->render_mode == 4) && !e->edit_flag)
		stereo_tracer(e);
	else
		ray_tracer(e);
	e->move_x = 0;
	e->move_y = 0;
	e->move_z = 0;
	e->rotate_x = 0;
	e->rotate_y = 0;
	e->rotate_z = 0;
}

void	set_mode(int keycode, t_env *e)
{
	if (keycode == KEY_ENTER)
	{
    	e->edit_flag = e->edit_flag == 1 ? 0 : 1;
    	e->help_flag = 0;
    	e->pixelize = 0;
    	e->render_mode = e->edit_flag == 1 ? 0 : e->render_mode;
    	e->am_flag = e->edit_flag == 1 ? 0 : e->am_flag;
		e->cel_shade = e->edit_flag == 1 ? 0 : e->cel_shade;
		e->stereo_flag = e->edit_flag == 1 ? 0 : e->stereo_flag;
		e->flag.deep = e->edit_flag == 1 ? 0 : e->flag.deep;
	}
    else if (keycode == KEY_H && e->edit_flag)
    	e->help_flag = e->help_flag == 1 ? 0 : 1;
    else if (keycode == KEY_SPACEBAR)
		e->pixelize = e->pixelize == 1 ? 0 : 1;
	else if (keycode == KEY_R)
		e->aa_flag = e->aa_flag == 1 ? 0 : 1;
	else if (keycode == KEY_T)
	{
    	e->am_flag = e->am_flag == 1 ? 0 : 1;
    	e->render_mode = e->am_flag == 1 ? 1 : 0;
	}
	else if (keycode == KEY_P)
	{
    	e->stereo_flag = e->stereo_flag == 1 ? 0 : 1;
    	e->render_mode = e->stereo_flag == 1 ? 2 : 0;
    	e->flag.deep = e->stereo_flag == 1 ? 0 : 1;

	}
	else if (keycode == KEY_C)
	{
		e->cel_shade = e->cel_shade == 1 ? 0 : 1;
		e->render_mode = e->cel_shade == 1 ? 3 : 0;
	}
	else if (keycode == KEY_F)
	{
    	e->flag.deep = e->flag.deep == 1 ? 0 : 1;
    	e->render_mode = e->flag.deep == 1 ? 4 : 0;
    	e->stereo_flag = e->flag.deep == 1 ? 0 : 1;
	}
}

int			key_functions(int keycode, t_env *e)
{
	if (!check_keycode(keycode, e))
		return (0);
	set_mode(keycode, e);
	printf("key %d\n", keycode);
	if (!inputs(keycode, e))
		return (0);
	inputs2(keycode, e);
		if (keycode == KEY_PAD_ADD)
			e->tmp_rad += 1;
		else if (keycode == KEY_PAD_SUB)
			e->tmp_rad -= 1;
		ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
		camera_transformation(e);
		// if (!((e->mlx.img_ptr = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
		// "./textures/thewood.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		// 	ft_kill("Texture error");
		// e->mlx.data = (unsigned char*)mlx_get_data_addr(e->mlx.img_ptr,
		// &e->mlx.bpp, &e->mlx.l_size, &e->mlx.endian);
		if (e->render_mode == 2 || e->render_mode == 4)
			reset_stereo(e);
	choose_display_mode(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr,
		0, 0);
	if (e->edit_flag && !e->help_flag)
		print_info(e);
	else if (e->edit_flag && e->help_flag)
		print_help(e);
	return (0);
}
