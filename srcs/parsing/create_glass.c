/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_glass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:19:53 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/06 15:19:54 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void create_child_glass(t_object *glass)
{
	t_object *g_cylinder;
	t_object *g_cone;
	t_object *g_sphere;
	t_vector tmp;

	g_cylinder = init_material();
	if (!(g_cylinder->type = ft_strdup("cylinder")))
		exit_rt(1);
	g_cylinder->center = glass->center;
	g_cylinder->lenght_max = glass->lenght_max;
	g_cylinder->radius = 10;
	g_cylinder->cap = 1;
	g_cylinder->color = glass->color;
	g_cylinder->axis = glass->axis;
	create_cap_cylinder(g_cylinder);
	debug_object(g_cylinder);
	add_new_object(&glass->sub_object, g_cylinder);
	g_cone = init_material();
	if (!(g_cone->type = ft_strdup("cone")))
		exit_rt(1);	
	g_cone->axis = v_double_mult(&glass->axis, -1.00);
	tmp = v_double_mult(&glass->axis, (g_cylinder->lenght_max * 0.7)/ 2);
	g_cone->center = v_v_subs(&glass->center, &tmp);
	g_cone->lenght_max =  glass->lenght_max;
	g_cone->radius = g_cylinder->radius;
	g_cone->cap = 1;
	g_cone->tangent = 1;
	g_cone->color = glass->color;
	create_cap_cone(g_cone);
	debug_object(g_cone);
	add_new_object(&glass->sub_object, g_cone);
	g_sphere = init_material();
	if (!(g_sphere->type = ft_strdup("sphere")))
		exit_rt(1);	
	g_sphere->normal = v_double_mult(&glass->axis, -1.00);
	tmp = v_double_mult(&glass->axis, (g_cylinder->lenght_max )/ 2 + g_cylinder->radius * 10);
	g_sphere->center = v_v_add(&glass->center, &tmp);
	g_sphere->radius =  g_cylinder->radius * 10;
	g_sphere->cap = 1;
	g_sphere->color = glass->color;
	create_cap_sphere(g_sphere);
	debug_object(g_sphere);
	add_new_object(&glass->sub_object, g_sphere);
}

void		create_glass_conditions(t_object *glass, t_json *tmp)
{
	if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		glass->center = parse_point(tmp->member);
	else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		glass->axis = parse_normal(tmp->member);
	else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
		glass->color = parse_color(tmp->member);
	else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
		glass->lenght_max = ft_atod(tmp->content);
	else if (!(ft_strcmp(tmp->name, "material")))
		parse_material(tmp, glass);
	else
		ft_printf("{R}WARNING:{E} plane as a bad attribut\n");
}

void create_glass(t_env *e, t_json *json)
{
	t_object	*glass;
	t_json		*tmp;

	glass = init_material();
	if (!(glass->type = ft_strdup("glass")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		create_glass_conditions(glass, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	create_child_glass(glass);
	debug_object(glass);
	add_new_object(&e->object, glass);
}