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
		if (ft_strcmp(json->member->name, "coord") == 0)
			plane->point = parse_point(json->member->member);
		else if (ft_strcmp(json->member->name, "normal") == 0)
			plane->normal = parse_normal(json->member->member);
		else if (ft_strcmp(json->member->name, "material") == 0)
			parse_material(json->member, plane);
		else if (ft_strcmp(json->member->name, "color") == 0)
			plane->color = parse_color(json->member->member);
		tmp = json->member;
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
		ft_putendl(json->member->name);
		if (ft_strcmp(json->member->name, "coord") == 0)
			sphere->center = parse_point(json->member->member);
		else if (ft_strcmp(json->member->name, "radius") == 0)
			sphere->radius = ft_atod(json->member->content);
		else if (ft_strcmp(json->member->name, "material") == 0)
			parse_material(json->member, sphere);
		else if (ft_strcmp(json->member->name, "color") == 0)
			sphere->color = parse_color(json->member->member);
		tmp = json->member;
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
		if (ft_strcmp(json->member->name, "coord") == 0)
			cylinder->center = parse_point(json->member->member);
		else if (ft_strcmp(json->member->name, "normal") == 0)
			cylinder->axis = parse_normal(json->member->member);
		else if (ft_strcmp(json->member->name, "radius") == 0)
			cylinder->radius = ft_atod(json->member->content);
		else if (ft_strcmp(json->member->name, "length") == 0)
			cylinder->lenght_max = ft_atod(json->member->content);
		else if (ft_strcmp(json->member->name, "material") == 0)
			parse_material(json->member, cylinder);
		else if (ft_strcmp(json->member->name, "color") == 0)
			cylinder->color = parse_color(json->member->member);
		tmp = json->member;
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
		if (ft_strcmp(json->member->name, "vertex") == 0)
			cone->vertex = parse_point(json->member->member);
		if (ft_strcmp(json->member->name, "tangent") == 0)
			cone->tangent = ft_atod(json->member->content);
		if (ft_strcmp(json->member->name, "lenght") == 0)
			cone->lenght_max = ft_atod(json->member->content);
		if (ft_strcmp(json->member->name, "axis") == 0)
			cone->axis = parse_point(json->member->member);
		else if (ft_strcmp(json->member->name, "material") == 0)
			parse_material(json->member, cone);
		else if (ft_strcmp(json->member->name, "color") == 0)
			cone->color = parse_color(json->member->member);
		tmp = json->member;
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	debug_object(cone);
	add_new_object(&e->object, cone);
}