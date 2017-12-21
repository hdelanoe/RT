// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   torus.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2017/11/28 14:09:37 by hdelanoe          #+#    #+#             */
// /*   Updated: 2017/11/28 14:09:39 by hdelanoe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "rtv1.h"

// t_torus		*add_new_torus(t_object *object, t_torus *new_torus)
// {
// 	t_torus	*tmp;

// 	tmp = object->start_torus;
// 	if (tmp)
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		new_torus->next = NULL;
// 		tmp->next = new_torus;
// 	}
// 	else
// 		object->start_torus = new_torus;
// 	return (tmp);
// }

// void		create_torus(t_object *object, char *line)
// {
// 	t_torus		*torus;
// 	int			i;

// 	torus = (t_torus*)ft_memalloc(sizeof(t_torus));
// 	object->tab_line = ft_strsplit(line, ' ');
// 	torus->center = set_vector(ft_atod(object->tab_line[1]), ft_atod(object->tab_line[2]), ft_atod(object->tab_line[3]));
// 	torus->big_radius = ft_atod(object->tab_line[4]);
// 	torus->small_radius = ft_atod(object->tab_line[5]);
// 	torus->axis = set_vector(ft_atod(object->tab_line[6]), ft_atod(object->tab_line[7]), ft_atod(object->tab_line[8]));
// 	torus->axis = normalize(&torus->axis);
// 	torus->color = set_color(ft_atod(object->tab_line[9]), ft_atod(object->tab_line[10]), ft_atod(object->tab_line[11]));
// 	torus->id = ft_atoi(object->tab_line[12]);
// 	i = 0;
// 	while (object->tab_line[i])
// 	{
// 		free(object->tab_line[i]);
// 		i++;
// 	}
// 	torus = add_new_torus(object, torus);
// }

// int		torus_intersection(t_datas *data, t_torus *torus)
// {
// 	double 		a;
// 	double		b;
// 	double		c;
// 	double      d;
// 	double      e;
// 	double  	m;
// 	double 		n;
// 	double 		o;
// 	double 		p;
// 	double 		q;
// 	double 		k;
// 	t_vector 		r;
// 	double 			s;
// 	double		s1;
// 	double		s2;
// 	double		discriminant;
// 	t_vector 	tmp;
// 	t_vector	torus_origin;
// 	t_vector	tmp_node;

// 	torus_origin = v_v_subs(&data->current_origin, &torus->center);

// 	m = dot_product(&data->current_rayon, &data->current_rayon);
// 	//printf("m = %f", m);
// 	n = dot_product(&data->current_rayon, &torus_origin);
// 	o = dot_product(&torus_origin, &torus_origin);
// 	p = dot_product(&data->current_rayon, &torus->axis);
// 	q = dot_product(&torus_origin, &torus->axis);
// 	a = pow(m, 2);
// 	b = (4 * m * n);
// 	c = ((4 * pow(m, 2)) + (2 * m * o) - (2 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * m) + (4 * pow(torus->big_radius, 2) * pow(p, 2)));
// 	d = ((4 * n * o) - (4 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * n) + (8 * pow(torus->big_radius, 2) * p * q));
// 	e = ((pow(o, 2)) - (2 * (pow(torus->big_radius, 2) + pow(torus->small_radius, 2)) * o) + (4 * pow(torus->big_radius, 2) * pow(q, 2)) + pow((pow(torus->big_radius, 2) - pow(torus->small_radius, 2)), 2));
// 	//printf("**%f  %f**\n", b, d);
// 	if (b == 0 && d == 0)
// 	{
// 		ft_putendl("LOL");
// 		discriminant = (c * c) - 4 * a * e;
// 		if (discriminant < 0)
// 			return (0);
// 		else
// 		{
// 			if (discriminant == 0)
// 				data->solution = - c;
// 			else
// 			{
// 				discriminant = sqrt(discriminant);
// 				s1 = sqrt((- c + discriminant));
// 				s2 = sqrt((- c - discriminant));
// 				data->solution = (s1 < s2) ? s1 : s2;
// 			}
// 		}
// 	}
// 	else if (b != 0 && a * pow(d, 2) == e * pow(b, 2))
// 		printf("LOL\n");
// 	tmp_node = v_double_mult(&data->current_rayon, data->solution);
// 	torus->node = v_v_add(&data->current_origin, &tmp_node);
// 	tmp = v_v_subs(&torus->node, &torus->center);
// 	k = dot_product(&tmp, &torus->axis);
// 	tmp = v_double_mult(&torus->axis, k);
// 	r = v_v_subs(&torus->node, &tmp);
// 	s = sqrt(pow(torus->small_radius, 2) - pow(k, 2));
// 	torus->node_normal = v_v_subs(&torus->node, &r);
// 	tmp = v_v_subs(&torus->center, &r);
// 	tmp = v_double_mult(&tmp, s);
// 	tmp = v_double_div(&tmp, torus->big_radius + s);
// 	torus->node_normal = v_v_subs(&torus->node_normal, &tmp);
// 	torus->node_normal = normalize(&torus->node_normal);
// 		return (1);
// }