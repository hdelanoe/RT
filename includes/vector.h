/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:06:00 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/01/11 16:06:02 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "../libft/libft.h"
# include "rtv1.h"

typedef struct s_vector	t_vector;

struct					s_vector
{
	double				x;
	double				y;
	double				z;
};

double					magnitude(t_vector *a);
double					dot_product(t_vector *a, t_vector *b);
t_vector				normalize(t_vector *a);
t_vector				set_vector(double x, double y, double z);
t_vector				v_v_add(t_vector *a, t_vector *b);
t_vector				v_v_subs(t_vector *a, t_vector *b);
t_vector				v_v_mult(t_vector *a, t_vector *b);
t_vector				v_double_add(t_vector *a, double b);
t_vector				v_double_subs(t_vector *a, double b);
t_vector				v_double_mult(t_vector *a, double b);
t_vector				v_double_div(t_vector *a, double b);

#endif
