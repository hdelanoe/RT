/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:12:46 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/08 18:12:47 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		turbulence(t_env *e, double x, double y, double z)
{
	int			i;
	double		coef;

	i = 0;
	coef = 0.0;
	while (i < 10)
	{
		coef += (1.0 / i)
		* fabs(noise(e, i * 0.05 * x, i * 0.05 * y, i * 0.05 * z));
		i++;
	}
	coef = 0.5 * sinf((x + y) * 0.05 + coef) + 0.5;
	return (coef);
}
