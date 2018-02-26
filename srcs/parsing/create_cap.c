/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:07:43 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 16:07:45 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	*init_cap(t_object *parent)
{
	t_object *cap;

	if (!(cap = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Error in malloc object");
	cap->id = -1;
	cap->radius = parent->radius;
	cap->color = parent->color;
	init_copy2(&cap, parent);
	if (!(cap->type = ft_strdup("disk")))
		exit_rt(1);
	return (cap);
}

void		create_cap_sphere(t_object *sphere)
{
	t_object *disk;

	disk = init_cap(sphere);
	disk->point = sphere->center;
	add_new_object(&sphere->sub_object, disk);
}

void		create_cap_cylinder(t_object *cylinder)
{
	t_object		*disk;
	t_vector		tmp;

	disk = init_cap(cylinder);
	disk->normal = cylinder->axis;
	tmp = v_double_mult(&cylinder->axis, cylinder->lenght_max / 2);
	disk->point = v_v_subs(&cylinder->center, &tmp);
	add_new_object(&cylinder->sub_object, disk);
	disk = init_cap(cylinder);
	disk->normal = cylinder->axis;
	disk->point = v_v_add(&cylinder->center, &tmp);
	add_new_object(&cylinder->sub_object, disk);
}

void		create_disk(t_env *e, t_json *json)
{
	t_object	*disk;
	t_json		*tmp;

	disk = init_material();
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	while (json->member)
	{
		if (ft_strcmp(json->member->name, "coord") == 0)
			disk->point = parse_point(json->member->member);
		else if (ft_strcmp(json->member->name, "normal") == 0)
			disk->normal = parse_normal(json->member->member);
		else if (ft_strcmp(json->member->name, "radius") == 0)
			disk->radius = ft_atod(json->member->content);
		else if (ft_strcmp(json->member->name, "material") == 0)
			parse_material(json->member, disk);
		else if (ft_strcmp(json->member->name, "color") == 0)
			disk->color = parse_color(json->member->member);
		tmp = json->member;
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	add_new_object(&e->object, disk);
}

void		create_cap_cone(t_object *cone)
{
	t_object		*disk;
	t_vector		tmp;

	disk = init_cap(cone);
	disk->normal = cone->axis;
	disk->radius = cone->tangent * cone->lenght_max;
	tmp = v_double_mult(&cone->axis, cone->lenght_max);
	disk->point = v_v_add(&tmp, &cone->center);
	add_new_object(&cone->sub_object, disk);
	if (cone->radius < cone->lenght_max)
	{
		disk = init_cap(cone);
		disk->normal = cone->axis;
		disk->radius = cone->tangent * cone->radius;
		tmp = v_double_mult(&cone->axis, cone->radius);
		disk->point = v_v_add(&tmp, &cone->center);
		add_new_object(&cone->sub_object, disk);
	}
}
