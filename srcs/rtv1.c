/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double phong(t_light *light, t_vector view, t_vector *node)
{
	double 		reflect;
	t_vector      tmp;
	double 		phong_color;
	t_vector	r;

	reflect =  dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);

	phong_color = 0.2 * powf(dot_product(&view, &r), 50) * 3;

	return (phong_color);
}

void	get_light(t_datas *d, t_object *object)
{
	int			light_blocked;
	t_vector	tmp_angle;
	t_color		color_to_add;
	t_color		tmp_color_to_add;
	t_light		*tmp_light;
	t_vector 	view_rayon;

	d->current_color = c_double_pow(&d->current_color, 2.2);
	view_rayon = d->current_rayon;
	tmp_light = object->start_light;
	d->color_finale = set_color(0, 0, 0);
	while (tmp_light)
	{
		light_blocked = 0;
		tmp_light->rayon = v_v_subs(&d->current_node, &tmp_light->origin);
		d->distance_light_object = magnitude(&tmp_light->rayon);
		tmp_light->rayon = normalize(&tmp_light->rayon);
		d->current_origin = tmp_light->origin;
		d->current_rayon = tmp_light->rayon;
		light_blocked = check_if_light_is_blocked(d, &light_blocked, object);
		if (light_blocked == 1)
			color_to_add = set_color(0, 0, 0);
		else
		{
			tmp_angle = v_double_mult(&tmp_light->rayon, (-1));
			tmp_light->angle = dot_product(&d->current_node_normal, &tmp_angle);
			if (tmp_light->angle <= 0)
				color_to_add = set_color(0, 0, 0);
			else
			{

				tmp_color_to_add = c_c_mult(&d->current_color, &tmp_light->color);
				tmp_color_to_add = c_double_pow(&tmp_color_to_add, 1/2.2);
				tmp_color_to_add = c_double_add(&tmp_color_to_add, phong(tmp_light, view_rayon, &d->current_node_normal));
				color_to_add = c_double_mult(&tmp_color_to_add, tmp_light->angle);
				
			}
		}
		d->color_finale = c_c_add(&d->color_finale, &color_to_add);
		tmp_light = tmp_light->next;
	}
}

void	get_intersection(t_datas *d, t_mlx *mlx, int x, int y, t_object *object)
{
	int			printable;
	t_cylinder	*tmp_cylinder;
	t_sphere	*tmp_sphere;
	t_cone		*tmp_cone;
	t_plane		*tmp_plane;
	t_torus		*tmp_torus;
	double reflect = 0;

	d->current_origin = d->camera.origin;
	d->current_rayon = d->camera.rayon;
	printable = 0;
	tmp_sphere = object->start_sphere;
	tmp_cylinder = object->start_cylinder;
	tmp_cone = object->start_cone;
	tmp_plane = object->start_plane;
	tmp_torus = object->start_torus;
	while (tmp_sphere)
	{
		if (sphere_intersection(d, tmp_sphere))
		{
			if (d->solution < d->distance)
			{
				printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_sphere->node;
				d->current_node_normal = tmp_sphere->node_normal;
				d->current_color = tmp_sphere->color;
				d->id_sphere = tmp_sphere->id;
				d->id_cylinder = -1;
				d->id_cone = -1;
				d->id_plane = -1;
				d->id_torus = -1;
			}
		}
		tmp_sphere = tmp_sphere->next;
	}
	while (tmp_cylinder)
	{
		if (cylinder_intersection(d, tmp_cylinder))
		{
			if (d->solution < d->distance)
			{
				printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_cylinder->node;
				d->current_node_normal = tmp_cylinder->node_normal;
				d->current_color = tmp_cylinder->color;
				d->id_cylinder = tmp_cylinder->id;
				d->id_sphere = -1;
				d->id_plane = -1;
				d->id_cone = -1;
				d->id_torus = -1;
			}
		}
		tmp_cylinder = tmp_cylinder->next;
	}
	while (tmp_cone)
	{
		if (cone_intersection(d, tmp_cone))
		{
			if (d->solution < d->distance)
			{
				printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_cone->node;
				d->current_node_normal = tmp_cone->node_normal;
				d->current_color = tmp_cone->color;
				d->id_cone = tmp_cone->id;
				d->id_sphere = -1;
				d->id_cylinder = -1;
				d->id_plane = -1;
				d->id_torus = -1;
			}
		}
		tmp_cone = tmp_cone->next;
	}
	while (tmp_plane)
	{
		if (plane_intersection(d, tmp_plane))
		{
			if (d->solution < d->distance)
			{
				reflect = 1;
				printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_plane->node;
				d->current_node_normal = tmp_plane->node_normal;
				d->current_color = tmp_plane->color;
				d->id_plane = tmp_plane->id;
				d->id_sphere = -1;
				d->id_cone = -1;
				d->id_cylinder = -1;
				d->id_torus = -1;
				/************   DAMIER SUR LE PLAN ***************/
//				int carre = floor(tmp_plane->node.x) + floor(tmp_plane->node.z);
//				if ((carre % 2) == 0)
//					d->current_color = set_color(0, 0, 0);
//				else
//					d->current_color = tmp_plane->color;
			}
		}
		tmp_plane = tmp_plane->next;
	}
	while (tmp_torus)
	{
		if (torus_intersection(d, tmp_torus))
		{
			if (d->solution < d->distance)
			{
				printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_torus->node;
				d->current_node_normal = tmp_torus->node_normal;
				d->current_color = tmp_torus->color;
				d->id_torus = tmp_torus->id;
				d->id_sphere = -1;
				d->id_cone = -1;
				d->id_cylinder = -1;
				d->id_plane = -1;
			}
		}
		tmp_torus = tmp_torus->next;
	}
	if (printable == 1)
	{
		t_color c = set_color(0, 0, 0); 
		t_vector view_rayon = d->current_rayon;
		t_vector node_normal = d->current_node_normal;
		t_vector node = d->current_node;

		get_light(d, object);
		if (reflect)
		{
			d->id_plane = -1;
			c = d->color_finale;

	
			reflect = dot_product(&view_rayon, &node_normal);
			t_vector tmp = v_double_mult(&node_normal, 2);
			tmp = v_double_mult(&tmp, reflect);
			t_vector r = v_v_subs(&view_rayon, &tmp);

			t_vector tmp2 = d->camera.rayon;
			tmp = d->camera.origin;

			d->camera.rayon = r;
			t_vector tmp3 = v_double_mult(&r, 0.001);
			d->camera.origin = v_v_add(&node, &tmp3);


			get_intersection(d, mlx, x, y, object);

			d->camera.rayon = tmp2;
			d->camera.origin = tmp;

		}
		t_color ctmp = c_c_add(&c, &d->color_finale);
		print_color(&ctmp, mlx, x, y);
	}
}

void	draw(t_datas *d, t_mlx *mlx, t_object *object)
{
	int			x;
	int			y;
	double		x1;
	double		y1;
	t_vector	viewplan_point;

	d->camera.origin = set_vector(0, 0, -(double)WIN_X);

	y = 0;
	y1 = (double)WIN_Y / 2;
	while (y < WIN_Y)
	{
		x = 0;
		x1 = -(double)WIN_X / 2;
		while (x < WIN_X)
		{
			d->distance = 100000;
			viewplan_point = set_vector(x1, y1, 0);
			d->camera.rayon = v_v_subs(&viewplan_point, &d->camera.origin);
			d->camera.rayon = normalize(&d->camera.rayon);
			get_intersection(d, mlx, x, y, object);
			x++;
			x1++;
		}
		y++;
		y1--;
	}
}
