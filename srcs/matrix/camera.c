/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 16:52:08 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	stereo_viewplane(t_env *e)
{
	t_vector	tmp_vpZ;
	t_vector	tmp_vpY;
	t_vector	tmp_vpX;

	tmp_vpX = v_double_mult(&e->lstereo.x_vector, (e->lstereo.width * 0.5));
	tmp_vpY = v_double_mult(&e->lstereo.y_vector, (e->lstereo.height * 0.5));
	tmp_vpZ = v_double_mult(&e->lstereo.z_vector, (e->lstereo.distance));
	e->lviewplane = v_v_add(&tmp_vpZ, &tmp_vpY);
	e->lviewplane = v_v_add(&e->lstereo.origin, &e->lviewplane);
	e->lviewplane = v_v_subs(&e->lviewplane, &tmp_vpX);
	tmp_vpX = v_double_mult(&e->rstereo.x_vector, (e->rstereo.width * 0.5));
	tmp_vpY = v_double_mult(&e->rstereo.y_vector, (e->rstereo.height * 0.5));
	tmp_vpZ = v_double_mult(&e->rstereo.z_vector, (e->rstereo.distance));
	e->rviewplane = v_v_add(&tmp_vpZ, &tmp_vpY);
	e->rviewplane = v_v_add(&e->rstereo.origin, &e->rviewplane);
	e->rviewplane = v_v_subs(&e->rviewplane, &tmp_vpX);
}

void	init_stereo(t_env *e)
{
	e->lstereo.origin = e->camera.origin;
	e->lstereo.up = set_vector(0, 1, 0);
	e->lstereo.width = (double)WIN_X;
	e->lstereo.height = (double)WIN_Y;
	e->lstereo.distance = (double)WIN_X;
	e->lstereo.z_vector = v_v_subs(&e->lookat, &e->lstereo.origin);
    e->lstereo.z_vector = normalize(&e->lstereo.z_vector);
    e->lstereo.y_vector = e->lstereo.up;
    e->lstereo.x_vector = v_v_mult(&e->lstereo.y_vector, &e->lstereo.z_vector);
    e->lstereo.y_vector = v_v_mult(&e->lstereo.z_vector, &e->lstereo.x_vector);
    e->rstereo.origin = set_vector(50, 0, -(double)WIN_X);
	e->rstereo.up = set_vector(0, 1, 0);
	e->rstereo.width = (double)WIN_X;
	e->rstereo.height = (double)WIN_Y;
	e->rstereo.distance = (double)WIN_X;
	e->rstereo.z_vector = v_v_subs(&e->lookat, &e->rstereo.origin);
    e->rstereo.z_vector = normalize(&e->rstereo.z_vector);
    e->rstereo.y_vector = e->rstereo.up;
    e->rstereo.x_vector = v_v_mult(&e->rstereo.y_vector, &e->rstereo.z_vector);
    e->rstereo.y_vector = v_v_mult(&e->rstereo.z_vector, &e->rstereo.x_vector);

    e->matrix_lstereo_system = matrix_camera_system(&e->lstereo.x_vector, &e->lstereo.y_vector, &e->lstereo.z_vector);
    e->matrix_lstereo_origin = matrix_camera_origin(&e->lstereo.origin);
    e->matrix_rstereo_system = matrix_camera_system(&e->rstereo.x_vector, &e->rstereo.y_vector, &e->rstereo.z_vector);
    e->matrix_rstereo_origin = matrix_camera_origin(&e->rstereo.origin);
    stereo_viewplane(e);
}

void	init_camera(t_env *e)
{
	e->camera.origin = set_vector(0, 0, -(double)WIN_X);
	e->camera.up = set_vector(0, 1, 0);
	e->camera.width = (double)WIN_X;
	e->camera.height = (double)WIN_Y;
	e->camera.distance = (double)WIN_X;
	e->camera.z_vector = v_v_subs(&e->lookat, &e->camera.origin);
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

void 	reset_stereo(t_env *e)
{ 	
    e->move_x = -50;
    e->translation_matrix = translation(e, &e->matrix_camera_system);
    e->matrix_lstereo_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix, &e->matrix_camera_origin);
    matrix_4x1_to_vectors(&e->lstereo.origin, &e->matrix_lstereo_origin);
    e->move_x = 50;
    e->translation_matrix = translation(e, &e->matrix_camera_system);
    e->matrix_rstereo_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix, &e->matrix_camera_origin);
    matrix_4x1_to_vectors(&e->rstereo.origin, &e->matrix_rstereo_origin);

    e->lstereo.z_vector = v_v_subs(&e->lookat, &e->lstereo.origin);
    e->lstereo.z_vector = normalize(&e->lstereo.z_vector);
    e->lstereo.x_vector = v_v_mult(&e->lstereo.y_vector, &e->lstereo.z_vector);
    e->lstereo.y_vector = v_v_mult(&e->lstereo.z_vector, &e->lstereo.x_vector);
  
   	e->rstereo.z_vector = v_v_subs(&e->lookat, &e->rstereo.origin);
    e->rstereo.z_vector = normalize(&e->rstereo.z_vector);
    e->rstereo.x_vector = v_v_mult(&e->rstereo.y_vector, &e->rstereo.z_vector);
    e->rstereo.y_vector = v_v_mult(&e->rstereo.z_vector, &e->rstereo.x_vector);
    stereo_viewplane(e);
}

void	viewplane_transformation(t_env *e)
{
	t_vector	tmp_vpZ;
	t_vector	tmp_vpY;
	t_vector	tmp_vpX;

	tmp_vpX = v_double_mult(&e->camera.x_vector, (e->camera.width * 0.5));
	tmp_vpY = v_double_mult(&e->camera.y_vector, (e->camera.height * 0.5));
	tmp_vpZ = v_double_mult(&e->camera.z_vector, (e->camera.distance));
	e->viewplane_point_up_left = v_v_add(&tmp_vpZ, &tmp_vpY);
	e->viewplane_point_up_left = v_v_add(&e->camera.origin, &e->viewplane_point_up_left);
	e->viewplane_point_up_left = v_v_subs(&e->viewplane_point_up_left, &tmp_vpX);
}
