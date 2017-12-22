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
		(*list) = new_object;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_object;
	(*list) = tmp;

}

void		create_plane(t_env *e, t_json *json)
{
	t_object	*plane;

	while (json->member)
	{
		plane = (t_object*)ft_memalloc(sizeof(t_object));
		plane->id = ft_atoi(json->member->name);
		if (!(plane->type = ft_strdup("plane")))
			exit_rt(1);
		init_material(plane);
		while(json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				plane->point = parse_point(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "normal") == 0)
				plane->normal = parse_normal(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "material") == 0)
				parse_material(json->member->member, plane);
			else
				exit_parser(1);
			json->member->member = json->member->member->next;
		}
	//	debug_plane(plane);
		add_new_object(&e->object, plane);
		json->member = json->member->next;
	}
}

void		create_sphere(t_env *e, t_json *json)
{
	t_object	*sphere;

	while (json->member)
	{
		sphere = (t_object*)ft_memalloc(sizeof(t_object));
		sphere->id = ft_atoi(json->member->name);
		sphere->type = ft_strdup("sphere");
		init_material(sphere);
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				sphere->center = parse_point(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "radius") == 0)
				sphere->radius = ft_atod(json->member->member->content);
			else if (ft_strcmp(json->member->member->name, "material") == 0)
				parse_material(json->member->member, sphere);
			else
				exit_parser(1);
			json->member->member = json->member->member->next;
		}
//		debug_sphere(sphere);
		add_new_object(&e->object, sphere);
		json->member = json->member->next;
	}
}

void		create_cylinder(t_env *e, t_json *json)
{
	t_object	*cylinder;

	while (json->member)
	{
		cylinder = (t_object*)ft_memalloc(sizeof(t_object));
		cylinder->id = ft_atoi(json->member->name);
		cylinder->type = ft_strdup("cylinder");
		init_material(cylinder);
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				cylinder->center = parse_point(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "normal") == 0)
				cylinder->axis = parse_normal(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "radius") == 0)
				cylinder->radius = ft_atod(json->member->member->content);
			else if (ft_strcmp(json->member->member->name, "length") == 0)
				cylinder->lenght_max = ft_atod(json->member->member->content);
			else if (ft_strcmp(json->member->member->name, "material") == 0)
				parse_material(json->member->member, cylinder);
			else
				exit_parser(1);
			json->member->member = json->member->member->next;
		}
//		debug_cylinder(cylinder);
		add_new_object(&e->object, cylinder);
		json->member = json->member->next;
	}
}

void		create_cone(t_env *e, t_json *json)
{
	t_object	*cone;

	while (json->member)
	{
		cone = (t_object*)ft_memalloc(sizeof(t_object));
		cone->id = ft_atod(json->member->name);
		cone->type = ft_strdup("cone");
		init_material(cone);
		while(json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "vertex") == 0)
				cone->vertex = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "tangent") == 0)
				cone->tangent = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "lenght") == 0)
				cone->lenght_max = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "axis") == 0)
				cone->axis = parse_point(json->member->member->member);
			else if (ft_strcmp(json->member->member->name, "material") == 0)
				parse_material(json->member->member, cone);
			else
				exit_parser(1);
			json->member->member = json->member->member->next;
		}
	//	cone->type = ft_strdup("cone");
		add_new_object(&e->object, cone);
		json->member = json->member->next;
	}
}
