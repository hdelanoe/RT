/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 19:19:34 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/05/28 20:09:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	mouse_cpy(t_env *e, int x, int y)
{
	if (copy_object(e, x, y))
	{
		if (e->copy)
		{
			mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 250,
				0xFFFFFF, e->copy->type);
			mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 100, 250,
				0xFFFFFF, "copied!");
			e->is_past = 1;
		}
	}
	else
		e->is_past = 0;
}

void	mouse_func(t_env *e, int x, int y, int button)
{
	if (!e->is_past && (button == 1 || button == 5) && !e->copy)
		mouse_cpy(e, x, y);
	else if (e->is_past && (button == 1 || button == 5) && e->copy)
	{
		add_object(e, x, y);
		e->is_past = 0;
	}
	else if ((button == 2 || button == 6) && !e->is_past && !e->copy)
	{
		if (obj_lst_size(&e->object) > 1)
		{
			delete_object(e, x, y);
		}
		else
		{
			ft_printf("Scene can't be empty.\n");
		}
	}
}

int		mouse(int button, int x, int y, t_env *e)
{
	if (!(x > 0 && x < WIN_X && y > 0 && y < WIN_Y) || !e->edit_flag)
		return (0);
	mouse_func(e, x, y, button);
	if ((e->stereo_flag || e->flag.deep) && (button == 1 || button == 5))
	{
		if (set_lookat(e, x, y))
		{
			reset_camera(e);
			reset_stereo(e);
			mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 250,
				0xFFFFFF, "POV set!");
			e->flag.lookat = 1;
		}
	}
	return (0);
}
