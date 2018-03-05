/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:33:24 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/28 19:33:25 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	inputs4(int keycode, t_env *e)
{
	if (keycode == KEY_L)
	{
		if (e->copy)
			check_copy_lst(e->copy);
		return (read_scene_files(e));
	}
	else if (keycode == KEY_K)
		return (read_obj_files(e));
	else if (keycode == KEY_O)
	{
		save_image(e);
		return (0);
	}
	else if (keycode == KEY_J)
	{
		save_scene(e);
		return (0);
	}
	return (1);
}
