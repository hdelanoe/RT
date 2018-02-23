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

void	create_obj_to_add(t_object **copy)
{
	if (!ft_strcmp((*copy)->type, "cylinder"))
		create_cap_cylinder((*copy));
	else if (!ft_strcmp((*copy)->type, "cone"))
		create_cap_cone((*copy));
	else if (!ft_strcmp((*copy)->type, "glass"))
		create_child_glass((*copy));
	else if (!ft_strcmp((*copy)->type, "sphere") && (*copy)->cap)
		create_cap_sphere((*copy));
}

int		set_lookat(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	if (cast_ray(e, e->camera.rayon, e->camera.origin))
	{
		e->lookat = e->current_node;
		return (1);
	}
	return (0);
}

int obj_lst_size(t_object **lst)
{
	int i;
	t_object *tmp;

	tmp = (*lst);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	mouse_func(t_env *e, int x, int y, int button)
{
	if (!e->is_past && (button == 1 || button == 5))
	{
		if (copy_object(e, x, y))
		{
			printf("la\n");
			if (e->copy && ft_strcmp("plane", e->copy->type))
			{
				mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 250,
					0xFFFFFF, e->copy->type);
				mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 100, 250,
					0xFFFFFF, "copied!");
				e->is_past = 1;
			}
			else
			{
				free(e->copy->type);
				free(e->copy);
				e->is_past = 0;
			}
		}
	}
	else if (e->is_past && (button == 1 || button == 5) && e->copy)
	{
		add_object(e, x, y);
		e->is_past = 0;
	}
	else if ((button == 2 || button == 6) && !e->is_past)
	{
		if (obj_lst_size(&e->object) > 1)
		{
			delete_object(e, x, y);
			e->is_past = 0;
		}
		else 
			ft_printf("Scene can't be empty.\n");
	}
}

int		mouse(int button, int x, int y, t_env *e)
{
	if (!(x > 0 && x < WIN_X && y > 0 && y < WIN_Y) || !e->edit_flag)
		return (0);
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
	mouse_func(e, x, y, button);
	return (0);
}
