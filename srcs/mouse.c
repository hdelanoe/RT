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

#include "rtv1.h"

void 	init_copy(t_object **copy, t_object *object)
{
	if (!((*copy) = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Error in malloc object");
	(*copy)->type = object->type;
	(*copy)->id = object->id;
	(*copy)->point = object->point;
	(*copy)->center = object->center;
	(*copy)->vertex = object->vertex;
	(*copy)->normal = object->normal;
	(*copy)->radius = object->radius;
	(*copy)->lenght_max = object->lenght_max;
	(*copy)->tangent = object->tangent;
	(*copy)->axis = object->axis;
	(*copy)->node = object->node;
	(*copy)->node_normal = object->node_normal;
	(*copy)->color = object->color;
	(*copy)->cap = object->cap;
	(*copy)->ambient = object->ambient;
	(*copy)->diffuse = object->diffuse;
	(*copy)->specular = object->specular;
	(*copy)->reflect = object->reflect;
	(*copy)->refract = object->refract;
	(*copy)->absorbtion = object->absorbtion;
	(*copy)->next = NULL;
}

void add_object(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_object	*copy;

	init_copy(&copy, e->copy);
	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	copy->center = viewplane_point;
	add_new_object(&e->object, copy);
	if (!ft_strcmp(copy->type, "cylinder") && copy->cap)
		if(copy->cap > 0)
			create_cap_cylinder(copy);
	if (!ft_strcmp(copy->type, "cone"))
		if(copy->cap > 0)
			create_cap_cone(copy);
	ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
	if (e->aa_flag == 1 && e->pixelize == 0)
		aa_tracer(e, 1);
	else if (e->pixelize == 1)
		pxl_tracer(e, 13);
	else
		ray_tracer(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr,
	0, 0);
}

int set_lookat(t_env *e, int x, int y)
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
	//	if (!((*copy) = (t_object*)ft_memalloc(sizeof(t_object))))
	//		ft_kill("Error in malloc object");
//		init_copy(copy, e->copy);
		e->lookat = e->current_node;
		return (1);
	}
	return (0);
}

int copy_object(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	e->is_copy = 1;
	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	if (cast_ray(e, e->camera.rayon, e->camera.origin))
	{
	//	if (!((*copy) = (t_object*)ft_memalloc(sizeof(t_object))))
	//		ft_kill("Error in malloc object");
//		init_copy(copy, e->copy);
		e->is_copy = 0;
		return (1);
	}
	return (0);
}

int		mouse(int button, int x, int y, t_env *e)
{
//	static t_object *copy;
	if (!e->edit_flag)
		return (0);
	if (e->stereo_flag && (button == 1 || button == 5))
	{
		if(set_lookat(e, x, y))
		{
			ft_bzero(e->mlx.data, (WIN_X * WIN_Y) * 4);
			camera_transformation(e);
			reset_stereo(e);
			e->stereo_flag = 0;
			stereo_tracer(e);
			mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
		}
	}
	else if (!e->is_past && (button == 1 || button == 5))
	{
		if (copy_object(e, x, y))
		{
			ft_printf("copy %s\n", e->copy->type);
			e->is_past = 1;
		}
	}
	else if (e->is_past && (button == 1 || button == 5))
	{
		ft_printf("past %s\n", e->copy->type);
		add_object(e, x, y);
	//	free(copy->type);
	//	ft_bzero(copy, sizeof(t_object*));
		e->is_past = 0;
	}
	return (0);
}
