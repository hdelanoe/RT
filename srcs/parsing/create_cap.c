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

void		create_cap_sphere(t_object *sphere)
{
	t_object *disk;

	disk = init_material();
	init_copy2(&disk, sphere);
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	disk->point = sphere->center;
	disk->normal = sphere->normal;
	disk->radius = sphere->radius;
	disk->color = sphere->color;
	add_new_object(&sphere->sub_object, disk);
}

void		create_cap_cylinder(t_object *cylinder)
{
	t_object		*disk;
	t_vector		tmp;

	disk = init_material();
	init_copy2(&disk, cylinder);
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	tmp = v_double_mult(&cylinder->axis, cylinder->lenght_max / 2);
	disk->point = v_v_subs(&cylinder->center, &tmp);
	disk->normal = cylinder->axis;
	disk->radius = cylinder->radius;
	disk->color = cylinder->color;
	add_new_object(&cylinder->sub_object, disk);
	disk = init_material();
	init_copy2(&disk, cylinder);
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	disk->normal = cylinder->axis;
	disk->radius = cylinder->radius;
	disk->color = cylinder->color;
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

	disk = init_material();
	init_copy2(&disk, cone);
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	tmp = v_double_mult(&cone->axis, cone->lenght_max);
	disk->point = v_v_add(&tmp, &cone->center);
	disk->normal = cone->axis;
	disk->radius = cone->tangent * cone->lenght_max;
	disk->color = cone->color;
	add_new_object(&cone->sub_object, disk);
	if (cone->radius < cone->lenght_max)
	{
		disk = init_material();
		init_copy2(&disk, cone);
		if (!(disk->type = ft_strdup("disk")))
			exit_rt(1);
		tmp = v_double_mult(&cone->axis, cone->radius);
		disk->point = v_v_add(&tmp, &cone->center);
		disk->normal = cone->axis;
		disk->radius = cone->tangent * cone->radius;
		disk->color = cone->color;
		add_new_object(&cone->sub_object, disk);
	}
}
