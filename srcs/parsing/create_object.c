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

	if (!(*list)->type)
	{
		free((*list));
		(*list) = new_object;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_object;
	(*list) = tmp;

}

void debug_object(t_object *tmp)
{
	t_vector origin;

	if (!(ft_strcmp(tmp->type, "sphere")))
			origin = tmp->center;
		else if (!(ft_strcmp(tmp->type, "plane")))
			origin = tmp->point;
		else if (!(ft_strcmp(tmp->type, "cylinder")))
			origin = tmp->center;
		else if (!(ft_strcmp(tmp->type, "cone")))
			origin = tmp->vertex;
	printf("OBJECT :%s %i\n", tmp->type, tmp->id);
	printf("origin : x->%f\n", origin.x);
	printf("         y->%f\n", origin.y);
	printf("         z->%f\n", origin.z);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}

void		create_plane(t_env *e, t_json *json, int *id)
{
	t_object	*plane;
	t_json		*tmp;

	plane = (t_object*)ft_memalloc(sizeof(t_object));
	plane->id = *id;
	*id += 1;
	if (!(plane->type = ft_strdup("plane")))
		exit_rt(1);
	init_material(plane);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			plane->point = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "normal")) && tmp->member)
			plane->normal = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			plane->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, plane);
		else
			ft_printf("{R}WARNING:{E} plane %d as a bad attribut\n", plane->id);
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_object(plane);
	add_new_object(&e->object, plane);
}

void		create_sphere(t_env *e, t_json *json, int *id)
{
	t_object	*sphere;
	t_json		*tmp;

	sphere = (t_object*)ft_memalloc(sizeof(t_object));
	sphere->id = *id;
	*id += 1;
	if (!(sphere->type = ft_strdup("sphere")))
		exit_rt(1);
	init_material(sphere);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			sphere->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
			sphere->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			sphere->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, sphere);
		else
			ft_printf("{R}WARNING:{E} sphere %d as a bad attribut\n", sphere->id);
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_object(sphere);
	add_new_object(&e->object, sphere);
}

void		create_cylinder(t_env *e, t_json *json, int *id)
{
	t_object	*cylinder;
	t_json		*tmp;

	cylinder = (t_object*)ft_memalloc(sizeof(t_object));
	cylinder->id = *id;
	*id += 1;
	if (!(cylinder->type = ft_strdup("cylinder")))
		exit_rt(1);
	init_material(cylinder);
	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			cylinder->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "normal")) && tmp->member)
			cylinder->axis = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "radius")) && tmp->content)
			cylinder->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
			cylinder->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cylinder->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, cylinder);
		else
			ft_printf("{R}WARNING:{E} cylinder %d as a bad attribut\n", cylinder->id);
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_object(cylinder);
	add_new_object(&e->object, cylinder);
}

void		create_cone(t_env *e, t_json *json, int *id)
{
	t_object	*cone;
	t_json 		*tmp;

	cone = (t_object*)ft_memalloc(sizeof(t_object));
	cone->id = *id;
	*id += 1;
	if (!(cone->type = ft_strdup("cone")))
		exit_rt(1);
	init_material(cone);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			cone->vertex = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "tangent")) &&tmp->content)
			cone->tangent = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
			cone->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
			cone->axis = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			cone->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, cone);
		else
			ft_printf("{R}WARNING:{E} cone %d as a bad attribut\n", cone->id);
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_object(cone);
	add_new_object(&e->object, cone);
}