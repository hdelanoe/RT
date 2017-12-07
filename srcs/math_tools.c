/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:59:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 19:59:33 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int poly_2nd_degree(t_datas **d, t_poly *p)
{
	p->discriminant = (p->b * p->b) - (4 * p->a * p->c);
	if (p->discriminant < 0)
		return (0);
	else
	{
		if (p->discriminant == 0)
			(*d)->solution = - (p->b / (2 * p->a));
		else
		{
			p->discriminant = sqrt(p->discriminant);
			p->s1 = (- p->b + p->discriminant) / (2 * p->a);
			p->s2 = (- p->b - p->discriminant) / (2 * p->a);
			(*d)->solution = (p->s1 < p->s2) ? p->s1 : p->s2;
		}
	}
	return (1);
}

int	poly_2nd_degree_sphere(t_datas *d, t_poly *p)
{
	p->discriminant = (p->b * p->b) - p->c;
	if (p->discriminant < 0)
		return (0);
	else
	{
		if (p->discriminant == 0)
			d->solution = - p->b;
		else
		{
			p->discriminant = sqrt(p->discriminant);
			p->s1 = (- p->b + p->discriminant);
			p->s2 = (- p->b - p->discriminant);
			d->solution = (p->s1 < p->s2) ? p->s1 : p->s2;
		}
	}
	return (1);
}
 
//double poly_4(t_poly *p)
//{
//	double tmp;
//
//	p->p = (-3 * pow(p->b, 2)) / (8 * pow(p->a ,2)) + p->c / p->a;
//	tmp = pow(p->b / 2, 3) / pow(p->a, 3);
//	p->q = tmp - (p->b * p->c / 2) / pow(p->a, 2) + p->d / p->a;
//	tmp = -3 * pow((b / 4) / a, 4) + c * (pow(b / 4, 2) / pow(a, 3));
//	p->r = tmp - (b * d / 4) / pow (a, 2) + e / a;
//}
