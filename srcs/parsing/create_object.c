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
	static int 		id = 1;

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
	// ft_printf("OBJECT :%s %i\n", tmp->type, tmp->id);
	// ft_printf("origin : x->%f\n", origin.x);
	// ft_printf("         y->%f\n", origin.y);
	// ft_printf("         z->%f\n", origin.z);
	// ft_printf("colors : r->%f\n", tmp->color.r);
	// ft_printf("         g->%f\n", tmp->color.g);
	// ft_printf("         b->%f\n", tmp->color.b);
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
		sphere_attribut(tmp, sphere);
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
		cylinder_attribut(cylinder, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
		create_cap_cylinder(cylinder);
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
			cone->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "minlength")) && tmp->content)
			cone->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
			cone->axis = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cone->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")))
			parse_material(tmp, cone);
		else
			ft_printf("{R}WARNING:{E} cone as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	if (cone->radius < 0)
		cone->radius *= -1;
	create_cap_cone(cone);
	debug_object(cone);
	add_new_object(&e->object, cone);
}