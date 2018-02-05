/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:35:40 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 15:55:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	degree_to_radian(double degree_angle)
{
	double		radian_angle;

	radian_angle = degree_angle * (2.0 * M_PI / 360.0);
	return (radian_angle);
}

void	camera_transformation(t_env *e)
{
	e->rotation_matrix = rotation(e->rotate_x, e->rotate_y, e->rotate_z);
	e->matrix_camera_system = m4x4_m4x4_mult(&e->matrix_camera_system,
			&e->rotation_matrix);
	matrix_4x4_to_vectors(&e->camera.x_vector, &e->camera.y_vector,
			&e->camera.z_vector, &e->matrix_camera_system);
	e->translation_matrix = translation(e, &e->matrix_camera_system);
	e->matrix_camera_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix,
			&e->matrix_camera_origin);
	matrix_4x1_to_vectors(&e->camera.origin, &e->matrix_camera_origin);
	viewplane_transformation(e);
}

void	reset_stereo(t_env *e)
{
	e->move_x = -33;
	e->translation_matrix = translation(e, &e->matrix_camera_system);
	e->matrix_lstereo_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix,
			&e->matrix_camera_origin);
	matrix_4x1_to_vectors(&e->lstereo.origin, &e->matrix_lstereo_origin);
	e->move_x = 33;
	e->translation_matrix = translation(e, &e->matrix_camera_system);
	e->matrix_rstereo_origin = m4x4_m4x1_mult_reduced(&e->translation_matrix,
			&e->matrix_camera_origin);
	matrix_4x1_to_vectors(&e->rstereo.origin, &e->matrix_rstereo_origin);
	e->lstereo.z_vector = v_v_subs(&e->lookat, &e->lstereo.origin);
	e->lstereo.z_vector = normalize(&e->lstereo.z_vector);
	e->lstereo.x_vector = v_v_mult(&e->camera.y_vector, &e->lstereo.z_vector);
	e->lstereo.y_vector = v_v_mult(&e->lstereo.z_vector, &e->lstereo.x_vector);
	e->rstereo.z_vector = v_v_subs(&e->lookat, &e->rstereo.origin);
	e->rstereo.z_vector = normalize(&e->rstereo.z_vector);
	e->rstereo.x_vector = v_v_mult(&e->camera.y_vector, &e->rstereo.z_vector);
	e->rstereo.y_vector = v_v_mult(&e->rstereo.z_vector, &e->rstereo.x_vector);
	stereo_viewplane(e);
}
