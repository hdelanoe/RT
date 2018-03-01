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
		if (read_scene_files(e))
			return (1);
		else
			return (0);
	}
	else if (keycode == KEY_K)
	{
		if (read_obj_files(e))
			return (1);
		else
			return (0);
	}
	return (1);
}
