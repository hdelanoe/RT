/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 01:26:00 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/27 01:26:02 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_diag(t_object **poly2, t_object *poly, t_parsing p)
{
	if (p.i > p.j && p.i > p.k)
	{
		(*poly2)->point_3 = poly->point_4;
		(*poly2)->point = poly->point;
		(*poly2)->point_2 = poly->point_2;
	}
	else if (p.j > p.i && p.j > p.k)
	{
		(*poly2)->point_2 = poly->point_4;
		(*poly2)->point = poly->point;
		(*poly2)->point_3 = poly->point_3;
	}
	else if (p.k > p.i && p.k > p.j)
	{
		(*poly2)->point = poly->point_4;
		(*poly2)->point_2 = poly->point_2;
		(*poly2)->point_3 = poly->point_3;
	}
}

void	set_poly_cb(t_env *e, t_object *poly)
{
	t_object	*poly2;
	t_parsing	p;

	poly2 = init_material();
	p.tmp1 = v_v_subs(&poly->point, &poly->point_2);
	p.tmp2 = v_v_subs(&poly->point, &poly->point_3);
	p.tmp3 = v_v_subs(&poly->point, &poly->point_4);
	p.i = magnitude(&p.tmp1);
	p.j = magnitude(&p.tmp2);
	p.k = magnitude(&p.tmp3);
	get_diag(&poly2, poly, p);
	if (!(poly2->type = ft_strdup("triangle")))
		exit_rt(1);
	add_new_object(&e->object, poly2);
}

void	set_poly(t_object **poly, char ***v, int tmp[4], char *f)
{
	(*poly)->point = set_vector(ft_atod(v[(int)tmp[0] - 1][1]),
	ft_atod(v[(int)tmp[0] - 1][2]), ft_atod(v[(int)tmp[0] - 1][3]));
	(*poly)->point_2 = set_vector(ft_atod(v[(int)tmp[1] - 1][1]),
	ft_atod(v[(int)tmp[1] - 1][2]), ft_atod(v[(int)tmp[1] - 1][3]));
	(*poly)->point_3 = set_vector(ft_atod(v[(int)tmp[2] - 1][1]),
	ft_atod(v[(int)tmp[2] - 1][2]), ft_atod(v[(int)tmp[2] - 1][3]));
	if (f)
		(*poly)->point_4 = set_vector(ft_atod(v[(int)tmp[3] - 1][1]),
	ft_atod(v[(int)tmp[3] - 1][2]), ft_atod(v[(int)tmp[3] - 1][3]));
}

void	parsing_obj(t_env *e, char ***v, char ***f)
{
	int			tmp[4];
	t_object	*poly;
	int			i;

	i = 0;
	while (f[i] && f[i][3])
	{
		poly = init_material();
		tmp[0] = ft_atoi(f[i][1]);
		tmp[1] = ft_atoi(f[i][2]);
		tmp[2] = ft_atoi(f[i][3]);
		if (f[i][4])
			tmp[3] = ft_atoi(f[i][4]);
		set_poly(&poly, v, tmp, f[i][4]);
		if (f[i][4])
			set_poly_cb(e, poly);
		if (!(poly->type = ft_strdup("triangle")))
			exit_rt(1);
		add_new_object(&e->object, poly);
		i++;
	}
}
