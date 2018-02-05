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

#include "rtv1.h"

void	cube1(t_cube *c, t_object *cube)
{
	c->carre_1 = init_material();
	if (!(c->carre_1->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_1->point = set_vector(cube->point.x , cube->point.y, cube->point.z);
	c->carre_1->point_2 = set_vector(cube->point.x, cube->point.y, cube->point.z + cube->tangent);
	c->carre_1->point_3 = set_vector(cube->point.x, cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_1->point_4 = set_vector(cube->point.x, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_1->color = cube->color;
	debug_object(c->carre_1);
	add_new_object(&cube->sub_object, c->carre_1);
	c->carre_2 = init_material();
	if (!(c->carre_2->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_2->point = cube->point;
	c->carre_2->point_2 = set_vector(cube->point.x, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_2->point_3 = set_vector(cube->point.x + cube->radius, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_2->point_4 = set_vector(cube->point.x + cube->radius, cube->point.y, cube->point.z);
	c->carre_2->color = cube->color;
	debug_object(c->carre_2);
	add_new_object(&cube->sub_object, c->carre_2);
}

void	cube2(t_cube *c, t_object *cube)
{
	c->carre_3 = init_material();
	if (!(c->carre_3->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_3->point = set_vector(cube->point.x + cube->radius, cube->point.y, cube->point.z);
	c->carre_3->point_2 = set_vector(cube->point.x + cube->radius, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_3->point_3 = set_vector(cube->point.x + cube->radius, cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_3->point_4 = set_vector(cube->point.x + cube->radius, cube->point.y, cube->point.z + cube->tangent);
	c->carre_3->color = cube->color;
	debug_object(c->carre_3);
	add_new_object(&cube->sub_object, c->carre_3);
	c->carre_4 = init_material();
	if (!(c->carre_4->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_4->point = set_vector(cube->point.x + cube->radius , cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_4->point_2 = set_vector(cube->point.x + cube->radius , cube->point.y, cube->point.z + cube->tangent);
	c->carre_4->point_4 = set_vector(cube->point.x , cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_4->point_3 = set_vector(cube->point.x, cube->point.y, cube->point.z + cube->tangent);
	c->carre_4->color = cube->color;
	debug_object(c->carre_4);
	add_new_object(&cube->sub_object, c->carre_4);
}

void	cube3(t_cube *c, t_object *cube)
{
	c->carre_5 = init_material();
	if (!(c->carre_5->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_5->point = set_vector(cube->point.x, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_5->point_2 = set_vector(cube->point.x, cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_5->point_3 = set_vector(cube->point.x + cube->radius, cube->point.y + cube->lenght_max, cube->point.z + cube->tangent);
	c->carre_5->point_4 = set_vector(cube->point.x  + cube->radius, cube->point.y + cube->lenght_max, cube->point.z);
	c->carre_5->color = cube->color;
	debug_object(c->carre_5);
	add_new_object(&cube->sub_object, c->carre_5);
	c->carre_6 = init_material();
	if (!(c->carre_6->type = ft_strdup("quad")))
		exit_rt(1);
	c->carre_6->point = set_vector(cube->point.x, cube->point.y, cube->point.z);
	c->carre_6->point_2 = set_vector(cube->point.x, cube->point.y, cube->point.z + cube->tangent);
	c->carre_6->point_3 = set_vector(cube->point.x + cube->radius, cube->point.y, cube->point.z + cube->tangent);
	c->carre_6->point_4 = set_vector(cube->point.x  + cube->radius, cube->point.y, cube->point.z);
	c->carre_6->color = cube->color;
	debug_object(c->carre_6);
	add_new_object(&cube->sub_object, c->carre_6);
}


void 	create_cap_cube(t_object *cube)
{
	t_cube	c;

	cube1(&c, cube);
	cube2(&c, cube);
	cube3(&c, cube);
}

void 		create_cube(t_env *e, t_json *json)
{
	t_object	*cube;
	t_json		*tmp;

	cube = init_material();
	if (!(cube->type = ft_strdup("cube")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			cube->point = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "width")))
			cube->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "length")))
			cube->tangent = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "height")))
			cube->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "axis")))
		{
			cube->axis = parse_normal(tmp->member);
			cube->axis = normalize(&cube->axis);
		}
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cube->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")))
			parse_material(tmp, cube);
		else
		{
			printf("%s\n",tmp->name );
			ft_printf("{R}WARNING:{E} cube as a bad attribut\n");
		}
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	cube->point = v_v_mult(&cube->point, &cube->axis);
	//cube->lenght_max *= cube->axis.x;
	//cube->tangent *= cube->axis.z;
	//cube->radius *= cube->axis.y;
	create_cap_cube(cube);
	debug_object(cube);
	add_new_object(&e->object, cube);
}
