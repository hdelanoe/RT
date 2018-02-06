/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:23 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/21 15:35:24 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		add_new_object(t_object **list, t_object *new_object)
{
	t_object	*tmp;
	int 		id;

	id = 1;
	if (!(*list))
	{
		new_object->id = id;
		(*list) = new_object;
		return ;
	}
	tmp = (*list);
	id++;
	while ((*list) && (*list)->next)
	{
		(*list) = (*list)->next;
		id++;
	}
	new_object->id = id;
	(*list)->next = new_object;
	(*list) = tmp;

}


void debug_object(t_object *tmp)
{
	t_vector origin;

	origin = tmp->center;
	if (!(ft_strcmp(tmp->type, "sphere")))
			origin = tmp->center;
		else if (!(ft_strcmp(tmp->type, "plane")))
			origin = tmp->point;
		else if (!(ft_strcmp(tmp->type, "quad")) || !(ft_strcmp(tmp->type, "quad")))
			origin = tmp->point;
		else if (!(ft_strcmp(tmp->type, "disk")))
			origin = tmp->point;
		else if (!(ft_strcmp(tmp->type, "triangle")))
			origin = tmp->point;
		else if (!(ft_strcmp(tmp->type, "cylinder")))
			origin = tmp->center;
		else if (!(ft_strcmp(tmp->type, "cone")))
			origin = tmp->center;
	printf("OBJECT :%s %i\n", tmp->type, tmp->id);
	printf("origin : x->%f\n", origin.x);
	printf("         y->%f\n", origin.y);
	printf("         z->%f\n", origin.z);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}





void		create_plane(t_env *e, t_json *json)
{
	t_object	*plane;
	t_json		*tmp;

	plane = init_material();
	if (!(plane->type = ft_strdup("plane")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		plane_attribut(plane, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	debug_object(plane);
	add_new_object(&e->object, plane);
}



void		create_sphere(t_env *e, t_json *json)
{
	t_object	*sphere;
	t_json		*tmp;

	sphere = init_material();
	if (!(sphere->type = ft_strdup("sphere")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			sphere->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
			sphere->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			sphere->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "plan_cut")) && tmp->member)
		{
			sphere->cap = 1;
			sphere->normal = parse_normal(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "material")))
			parse_material(tmp, sphere);
		else
			ft_printf("{R}WARNING:{E} sphere as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	debug_object(sphere);
	add_new_object(&e->object, sphere);
}

void		create_cylinder(t_env *e, t_json *json)
{
	t_object	*cylinder;
	t_json		*tmp;

	cylinder = init_material();
	if (!(cylinder->type = ft_strdup("cylinder")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			cylinder->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
			cylinder->axis = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
			cylinder->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
		{
			cylinder->cap = 1;
			cylinder->lenght_max = ft_atod(tmp->content);
		}
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cylinder->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")))
			parse_material(tmp, cylinder);
		else
			ft_printf("{R}WARNING:{E} cylinder as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	if (cylinder->lenght_max > 0)
		create_cap_cylinder(cylinder);
	else
		cylinder->lenght_max = 100000;
	debug_object(cylinder);
	add_new_object(&e->object, cylinder);
}

void		create_cone(t_env *e, t_json *json)
{
	t_object	*cone;
	t_json 		*tmp;

	cone = init_material();
	if (!(cone->type = ft_strdup("cone")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			cone->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "tangent")) &&tmp->content)
			cone->tangent = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "maxlength")) && tmp->content)
		{
			cone->cap = 1;
			cone->lenght_max = ft_atod(tmp->content);
		}
		else if (!(ft_strcmp(tmp->name, "minlength")) && tmp->content)
			cone->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
		{
			cone->axis = parse_point(tmp->member);
			cone->axis = normalize(&cone->axis);
		}
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cone->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")))
			parse_material(tmp, cone);
		else
			ft_printf("{R}WARNING:{E} cone as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	// CHECK IF MAX_LENGHT < MIN_LENGHT  FT_SWAP
	if (cone->lenght_max > 0 || cone->radius)
		create_cap_cone(cone);
	else
	{
		cone->lenght_max = 10000;
		cone->radius = 10000;
	}
	debug_object(cone);
	add_new_object(&e->object, cone);
}