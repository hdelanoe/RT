/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:06:00 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/11 16:06:02 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "../libft/libft.h"
# include "rtv1.h"

typedef struct		s_matrix4x4
{
	double			m[4][4];
}					t_matrix4x4;

typedef struct		s_matrix4x1
{
	double			m[4][1];
}					t_matrix4x1;

double				degree_to_radian(double degree_angle);
t_matrix4x4			rotation
(double degree_x, double degree_y, double degree_z);
t_matrix4x4			m4x4_m4x4_mult
(t_matrix4x4 *camera_matrix, t_matrix4x4 *rotation);
t_matrix4x1			m4x4_m4x1_mult_reduced
(t_matrix4x4 *translation, t_matrix4x1 *matrix);

#endif
