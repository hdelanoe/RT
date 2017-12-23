/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_camera(t_env *e)
{
	e->camera.origin = set_vector(0, 0, -(double)WIN_X);
	e->camera.lookat = set_vector(0, 0, 0);
	e->camera.up = set_vector(0, 1, 0);
	e->camera.viewplane_width = (double)WIN_X;
	e->camera.viewplane_height = (double)WIN_Y;
	e->camera.viewplane_distance = (double)WIN_X;
	e->camera.z_vector = v_v_subs(&e->camera.lookat, &e->camera.origin);
    e->camera.z_vector = normalize(&e->camera.z_vector);
    e->camera.y_vector = e->camera.up;
    e->camera.x_vector = v_v_mult(&e->camera.y_vector, &e->camera.z_vector);
    e->camera.y_vector = v_v_mult(&e->camera.z_vector, &e->camera.x_vector);
    e->matrix_camera_system = matrix_camera_system(&e->camera.x_vector, &e->camera.y_vector, &e->camera.z_vector);
    e->matrix_camera_origin = matrix_camera_origin(&e->camera.origin);
    viewplane_transformation(e);
}


void	camera_transformation(t_env *e)
{
    e->rotation_matrix = rotation(e->rotate_x, e->rotate_y, e->rotate_z);
    e->matrix_camera_system = m4x4_m4x4_mult(&e->matrix_camera_system, &e->rotation_matrix);
    matrix_4x4_to_vectors(&e->camera.x_vector, &e->camera.y_vector, &e->camera.z_vector, &e->matrix_camera_system);
    e->translation_matrix = translation(e, &e->matrix_camera_system);
    e->matrix_camera_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix, &e->matrix_camera_origin);
    matrix_4x1_to_vectors(&e->camera.origin, &e->matrix_camera_origin);
    viewplane_transformation(e);
}

void	viewplane_transformation(t_env *e)
{
	t_vector	tmp_vpZ;
	t_vector	tmp_vpY;
	t_vector	tmp_vpX;

	tmp_vpX = v_double_mult(&e->camera.x_vector, (e->camera.viewplane_width * 0.5));
	tmp_vpY = v_double_mult(&e->camera.y_vector, (e->camera.viewplane_height * 0.5));
	tmp_vpZ = v_double_mult(&e->camera.z_vector, (e->camera.viewplane_distance));
	e->viewplane_point_up_left = v_v_add(&tmp_vpZ, &tmp_vpY);
	e->viewplane_point_up_left = v_v_add(&e->camera.origin, &e->viewplane_point_up_left);
	e->viewplane_point_up_left = v_v_subs(&e->viewplane_point_up_left, &tmp_vpX);
}
