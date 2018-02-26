/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:46:24 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/31 12:46:25 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		init_copy2(t_object **copy, t_object *object)
{
	(*copy)->ambient = object->ambient;
	(*copy)->diffuse = object->diffuse;
	(*copy)->specular = object->specular;
	(*copy)->reflect = object->reflect;
	(*copy)->refract = object->refract;
	(*copy)->bump = object->bump;
	(*copy)->indice = object->indice;
	(*copy)->absorbtion = object->absorbtion;
	(*copy)->sub_object = NULL;
	(*copy)->next = NULL;
}

void		init_copy(t_object **copy, t_object *object)
{
	if (!((*copy) = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Error in malloc object");
	(*copy)->type = ft_strdup(object->type);
	(*copy)->point = object->point;
	(*copy)->point_2 = object->point_2;
	(*copy)->point_3 = object->point_3;
	(*copy)->point_4 = object->point_4;
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
	init_copy2(copy, object);
}

void		add_object(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;
	t_object	*copy;

	init_copy(&copy, e->copy);
	free(e->copy->type);
	free(e->copy);
	e->copy = NULL;
	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	copy->center = viewplane_point;
	copy_cplx(copy, viewplane_point);
	create_obj_to_add(&copy);
	add_new_object(&e->object, copy);
	ft_bzero(e->mlx.data, (e->width * e->height) * 4);
	choose_display_mode(e);
	if (e->edit_flag)
		print_info(e);
}

int			copy_object(t_env *e, int x, int y)
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
		return (1);
	return (0);
}

int			delete_object(t_env *e, int x, int y)
{
	t_vector	viewplane_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	e->is_delete = 1;
	tmp_vp_pointx = v_double_mult(&e->camera.x_vector, x);
	tmp_vp_pointy = v_double_mult(&e->camera.y_vector, y);
	viewplane_point = v_v_add(&e->viewplane_point_up_left, &tmp_vp_pointx);
	viewplane_point = v_v_subs(&viewplane_point, &tmp_vp_pointy);
	e->camera.rayon = v_v_subs(&viewplane_point, &e->camera.origin);
	e->camera.rayon = normalize(&e->camera.rayon);
	if (cast_ray(e, e->camera.rayon, e->camera.origin))
	{
		ft_object_remove_if(&e->object, e->id_object, (*cmp));
		ft_bzero(e->mlx.data, (e->width * e->height) * 4);
		choose_display_mode(e);
		if (e->edit_flag)
			print_info(e);
		return (1);
	}
	return (0);
}
