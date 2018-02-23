/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/05 15:46:09 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	stereo_viewplane(t_env *e)
{
	t_vector	tmp_vpz;
	t_vector	tmp_vpy;
	t_vector	tmp_vpx;

	tmp_vpx = v_double_mult(&e->lstereo.x_vector, (e->lstereo.width * 0.5));
	tmp_vpy = v_double_mult(&e->lstereo.y_vector, (e->lstereo.height * 0.5));
	tmp_vpz = v_double_mult(&e->lstereo.z_vector, (e->lstereo.distance));
	e->lviewplane = v_v_add(&tmp_vpz, &tmp_vpy);
	e->lviewplane = v_v_add(&e->lstereo.origin, &e->lviewplane);
	e->lviewplane = v_v_subs(&e->lviewplane, &tmp_vpx);
	tmp_vpx = v_double_mult(&e->rstereo.x_vector, (e->rstereo.width * 0.5));
	tmp_vpy = v_double_mult(&e->rstereo.y_vector, (e->rstereo.height * 0.5));
	tmp_vpz = v_double_mult(&e->rstereo.z_vector, (e->rstereo.distance));
	e->rviewplane = v_v_add(&tmp_vpz, &tmp_vpy);
	e->rviewplane = v_v_add(&e->rstereo.origin, &e->rviewplane);
	e->rviewplane = v_v_subs(&e->rviewplane, &tmp_vpx);
}

void	init_stereo(t_env *e)
{
	e->lstereo.origin = set_vector(-50, 0, -(double)WIN_X);
	e->lstereo.width = (double)WIN_X;
	e->lstereo.height = (double)WIN_Y;
	e->lstereo.distance = (double)WIN_X;
	e->lstereo.z_vector = v_v_subs(&e->lookat, &e->lstereo.origin);
	e->lstereo.z_vector = normalize(&e->lstereo.z_vector);
	e->lstereo.y_vector = set_vector(0, 1, 0);
	e->lstereo.x_vector = v_v_mult(&e->lstereo.y_vector, &e->lstereo.z_vector);
	e->lstereo.y_vector = v_v_mult(&e->lstereo.z_vector, &e->lstereo.x_vector);
	e->rstereo.origin = set_vector(50, 0, -(double)WIN_X);
	e->rstereo.width = (double)WIN_X;
	e->rstereo.height = (double)WIN_Y;
	e->rstereo.distance = (double)WIN_X;
	e->rstereo.z_vector = v_v_subs(&e->lookat, &e->rstereo.origin);
	e->rstereo.z_vector = normalize(&e->rstereo.z_vector);
	e->rstereo.y_vector = set_vector(0, 1, 0);
	e->rstereo.x_vector = v_v_mult(&e->rstereo.y_vector, &e->rstereo.z_vector);
	e->rstereo.y_vector = v_v_mult(&e->rstereo.z_vector, &e->rstereo.x_vector);
	e->matrix_lstereo_system = matrix_camera_system(&e->lstereo.x_vector,
			&e->lstereo.y_vector, &e->lstereo.z_vector);
	e->matrix_lstereo_origin = matrix_camera_origin(&e->lstereo.origin);
	e->matrix_rstereo_system = matrix_camera_system(&e->rstereo.x_vector,
			&e->rstereo.y_vector, &e->rstereo.z_vector);
	e->matrix_rstereo_origin = matrix_camera_origin(&e->rstereo.origin);
	stereo_viewplane(e);
}

void	init_camera(t_env *e)
{
	e->camera.up = set_vector(0, 1, 0);
	// e->camera.width = (double)WIN_X;
	// e->camera.height = (double)WIN_Y;
	e->camera.distance = 1000.0;
	e->camera.z_vector = v_v_subs(&e->lookat, &e->camera.origin);
	e->camera.z_vector = normalize(&e->camera.z_vector);
	e->camera.y_vector = e->camera.up;
	e->camera.x_vector = v_v_mult(&e->camera.y_vector, &e->camera.z_vector);
	e->camera.y_vector = v_v_mult(&e->camera.z_vector, &e->camera.x_vector);
	e->matrix_camera_system = matrix_camera_system(&e->camera.x_vector,
			&e->camera.y_vector, &e->camera.z_vector);
	e->matrix_camera_origin = matrix_camera_origin(&e->camera.origin);
	viewplane_transformation(e);
}

void	reset_camera(t_env *e)
{
	e->camera.z_vector = v_v_subs(&e->lookat, &e->camera.origin);
	e->camera.z_vector = normalize(&e->camera.z_vector);
	e->camera.x_vector = v_v_mult(&e->camera.y_vector, &e->camera.z_vector);
	e->camera.y_vector = v_v_mult(&e->camera.z_vector, &e->camera.x_vector);
	e->matrix_camera_system = matrix_camera_system(&e->camera.x_vector,
			&e->camera.y_vector, &e->camera.z_vector);
	e->matrix_camera_origin = matrix_camera_origin(&e->camera.origin);
	viewplane_transformation(e);
}

void	viewplane_transformation(t_env *e)
{
	t_vector	tmp_vpz;
	t_vector	tmp_vpy;
	t_vector	tmp_vpx;

	tmp_vpx = v_double_mult(&e->camera.x_vector, (e->camera.width * 0.5));
	tmp_vpy = v_double_mult(&e->camera.y_vector, (e->camera.height * 0.5));
	tmp_vpz = v_double_mult(&e->camera.z_vector, (e->camera.distance));
	e->viewplane_point_up_left = v_v_add(&tmp_vpz, &tmp_vpy);
	e->viewplane_point_up_left = v_v_add(&e->camera.origin,
			&e->viewplane_point_up_left);
	e->viewplane_point_up_left = v_v_subs(&e->viewplane_point_up_left,
			&tmp_vpx);
}
