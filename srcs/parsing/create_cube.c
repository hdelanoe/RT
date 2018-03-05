/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:11:46 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 16:11:47 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cube1(t_cube *c, t_object *cb)
{
	c->carre_1 = init_cap(cb);
	free(c->carre_1->type);
	if (!(c->carre_1->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_1->point = cb->point;
	c->carre_1->point_2 = set_vector(cb->point.x, cb->point.y,
	cb->point.z + cb->tangent);
	c->carre_1->point_3 = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z + cb->tangent);
	c->carre_1->point_4 = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z);
	c->carre_1->color = cb->color;
	add_new_object(&cb->sub_object, c->carre_1);
	c->carre_2 = init_cap(cb);
	free(c->carre_2->type);
	if (!(c->carre_2->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_2->point = cb->point;
	c->carre_2->point_2 = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z);
	c->carre_2->point_3 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y + cb->radius, cb->point.z);
	c->carre_2->point_4 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y, cb->point.z);
	c->carre_2->color = cb->color;
	add_new_object(&cb->sub_object, c->carre_2);
}

void		cube2(t_cube *c, t_object *cb)
{
	c->carre_3 = init_cap(cb);
	free(c->carre_3->type);
	if (!(c->carre_3->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_3->point = set_vector(cb->point.x + cb->lenght_max, cb->point.y,
	cb->point.z);
	c->carre_3->point_2 = set_vector(cb->point.x + cb->lenght_max, cb->point.y
	+ cb->radius, cb->point.z);
	c->carre_3->point_3 = set_vector(cb->point.x + cb->lenght_max, cb->point.y
	+ cb->radius, cb->point.z + cb->tangent);
	c->carre_3->point_4 = set_vector(cb->point.x + cb->lenght_max, cb->point.y,
	cb->point.z + cb->tangent);
	c->carre_3->color = cb->color;
	add_new_object(&cb->sub_object, c->carre_3);
	c->carre_4 = init_cap(cb);
	free(c->carre_4->type);
	if (!(c->carre_4->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_4->point = set_vector(cb->point.x + cb->lenght_max, cb->point.y +
	cb->radius, cb->point.z + cb->tangent);
	c->carre_4->point_2 = set_vector(cb->point.x + cb->lenght_max, cb->point.y,
	cb->point.z + cb->tangent);
	c->carre_4->point_4 = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z + cb->tangent);
	c->carre_4->point_3 = set_vector(cb->point.x, cb->point.y,
	cb->point.z + cb->tangent);
	add_new_object(&cb->sub_object, c->carre_4);
}

void		cube3(t_cube *c, t_object *cb)
{
	c->carre_5 = init_cap(cb);
	free(c->carre_5->type);
	if (!(c->carre_5->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_5->point = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z);
	c->carre_5->point_2 = set_vector(cb->point.x, cb->point.y +
	cb->radius, cb->point.z + cb->tangent);
	c->carre_5->point_3 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y + cb->radius, cb->point.z + cb->tangent);
	c->carre_5->point_4 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y + cb->radius, cb->point.z);
	c->carre_5->color = cb->color;
	add_new_object(&cb->sub_object, c->carre_5);
	c->carre_6 = init_cap(cb);
	free(c->carre_6->type);
	if (!(c->carre_6->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_6->point = set_vector(cb->point.x, cb->point.y, cb->point.z);
	c->carre_6->point_2 = set_vector(cb->point.x, cb->point.y,
	cb->point.z + cb->tangent);
	c->carre_6->point_3 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y, cb->point.z + cb->tangent);
	c->carre_6->point_4 = set_vector(cb->point.x + cb->lenght_max,
	cb->point.y, cb->point.z);
	c->carre_6->color = cb->color;
	add_new_object(&cb->sub_object, c->carre_6);
}

void		create_cap_cube(t_object *cb)
{
	t_cube	c;

	cube1(&c, cb);
	cube2(&c, cb);
	cube3(&c, cb);
}

void		create_cube(t_env *e, t_json *json)
{
	t_object	*cb;
	t_json		*tmp;

	cb = init_material();
	if (!(cb->type = ft_strdup("cube")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		cube_attribut(cb, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	create_cap_cube(cb);
	add_new_object(&e->object, cb);
}
