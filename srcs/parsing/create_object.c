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
		free((*list));
		new_object->id = 1;
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
		else if (!(ft_strcmp(tmp->type, "triangle")))
			origin = tmp->point_1;
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

void create_cap_sphere(t_object *sphere)
{
	t_object *disk;

	disk = init_material();
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	disk->point = sphere->center;
	disk->normal = sphere->normal;
	disk->radius = sphere->radius;
	disk->color = sphere->color;
	debug_object(disk);
	add_new_object(&sphere->sub_object, disk);
}

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
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
		{
			glass->center = parse_point(tmp->member);
		}
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
			glass->axis = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			glass->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "length")) && tmp->content)
			glass->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, glass);
		else
			ft_printf("{R}WARNING:{E} plane as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	create_child_glass(glass);
	debug_object(glass);
	add_new_object(&e->object, glass);
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
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			plane->point = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "normal")) && tmp->member)
			plane->normal = parse_normal(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			plane->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, plane);
		else
			ft_printf("{R}WARNING:{E} plane as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	debug_object(plane);
	add_new_object(&e->object, plane);
}

void		create_triangle(t_env *e, t_json *json)
{
	t_object	*triangle;
	t_json		*tmp;

	triangle = init_material();
	if (!(triangle->type = ft_strdup("triangle")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord_1")) && tmp->member)
			triangle->point = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "coord_2")) && tmp->member)
			triangle->point_2 = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "coord_3")) && tmp->member)
			triangle->point_3 = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			triangle->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, triangle);
		else
			ft_printf("{R}WARNING:{E} triangle as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	debug_object(triangle);
	add_new_object(&e->object, triangle);
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
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, sphere);
		else
			ft_printf("{R}WARNING:{E} sphere as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	if (sphere->cap)
		create_cap_sphere(sphere);
	debug_object(sphere);
	add_new_object(&e->object, sphere);
}

void create_cap_cylinder(t_object *cylinder)
{
	t_object *disk;

	disk = init_material();
		if (!(disk->type = ft_strdup("disk")))
			exit_rt(1);
	t_vector tmp = v_double_mult(&cylinder->axis, cylinder->lenght_max / 2);
	disk->point = v_v_subs(&cylinder->center, &tmp);
	disk->normal = cylinder->axis;
	disk->radius = cylinder->radius;
	disk->color = cylinder->color;
	debug_object(disk);
	add_new_object(&cylinder->sub_object, disk);
	disk = init_material();
		if (!(disk->type = ft_strdup("disk")))
			exit_rt(1);
	disk->normal = cylinder->axis;
	disk->radius = cylinder->radius;
	disk->color = cylinder->color;
	disk->point = v_v_add(&cylinder->center, &tmp);
	debug_object(disk);
	add_new_object(&cylinder->sub_object, disk);
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
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, cylinder);
		else
			ft_printf("{R}WARNING:{E} cylinder as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	if (cylinder->cap > 0)
		create_cap_cylinder(cylinder);
	else
		cylinder->lenght_max = 100000;
	debug_object(cylinder);
	add_new_object(&e->object, cylinder);
}

void create_disk(t_env *e, t_json *json)
{
	t_object	*disk;
	t_json		*tmp;

	disk = init_material();
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	while(json->member)
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
	debug_object(disk);
	add_new_object(&e->object, disk);
}

void create_cap_cone(t_object *cone)
{
	t_object *disk;
	t_vector tmp;

	disk = init_material();
	if (!(disk->type = ft_strdup("disk")))
		exit_rt(1);
	tmp = v_double_mult(&cone->axis, cone->lenght_max);
	disk->point = v_v_add(&tmp, &cone->center);
	disk->normal = cone->axis;
	disk->radius = cone->tangent * cone->lenght_max;
	disk->color = cone->color;
	debug_object(disk);
	add_new_object(&cone->sub_object, disk);
	if (cone->radius < cone->lenght_max)
	{
		disk = init_material();
		if (!(disk->type = ft_strdup("disk")))
			exit_rt(1);
		tmp = v_double_mult(&cone->axis, cone->radius);
		disk->point = v_v_add(&tmp, &cone->center);
		disk->normal = cone->axis;
		disk->radius = cone->tangent * cone->radius;
		disk->color = cone->color;
		debug_object(disk);
		add_new_object(&cone->sub_object, disk);
	}

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
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
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

void		create_torus(t_env *e, t_json *json)
{
	t_object	*torus;
	t_json 		*tmp;

	torus = init_material();
	if (!(torus->type = ft_strdup("torus")))
		exit_rt(1);
	while(json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "coord")) && tmp->member)
			torus->center = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "sradius")) &&tmp->content)
			torus->radius = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "bradius")) && tmp->content)
			torus->lenght_max = ft_atod(tmp->content);
		else if (!(ft_strcmp(tmp->name, "axis")) && tmp->member)
			torus->axis = parse_point(tmp->member);
		else if (!(ft_strcmp(tmp->name, "color")) && tmp->member)
			torus->color = parse_color(tmp->member);
		else if (!(ft_strcmp(tmp->name, "material")) && tmp->member)
			parse_material(tmp, torus);
		else
			ft_printf("{R}WARNING:{E} torus as a bad attribut\n");
		json->member = json->member->next;
		free_json_member(&tmp);
	}
	debug_object(torus);
	add_new_object(&e->object, torus);
}
