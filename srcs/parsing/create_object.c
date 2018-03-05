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

#include "rt.h"

void		add_new_object(t_object **list, t_object *new_object)
{
	t_object		*tmp;
	static int		id = 1;

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

void		create_plane(t_env *e, t_json *json)
{
	t_object	*plane;
	t_json		*tmp;

	plane = init_material();
	if (!(plane->type = ft_strdup("plane")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		plane_attribut(plane, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
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
	if (sphere->radius < 0)
		sphere->radius *= -1;
	if (sphere->cap == 1)
		create_cap_sphere(sphere);
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
	if (cylinder->lenght_max < 0)
		cylinder->lenght_max *= -1;
	if (cylinder->radius < 0)
		cylinder->radius *= -1;
	create_cap_cylinder(cylinder);
	add_new_object(&e->object, cylinder);
}

void		create_cone(t_env *e, t_json *json)
{
	t_object	*cone;
	t_json		*tmp;

	cone = init_material();
	if (!(cone->type = ft_strdup("cone")))
		exit_rt(1);
	while (json->member)
	{
		tmp = json->member;
		cone_attribut(cone, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	if (cone->radius < 0)
		cone->radius *= -1;
	if (cone->radius > cone->lenght_max)
		cone->radius = 0;
	create_cap_cone(cone);
	add_new_object(&e->object, cone);
}
