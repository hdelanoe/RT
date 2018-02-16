/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:30:19 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 16:03:46 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void 	print_create_menu(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 50,
		0xAAFFFF, "-- RT CREATE MODE --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 100,
		0xFFFFFF, "-- CHOOSE YOUR OBJECT --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 150,
		0xFFFFFF, "PLANE = 1");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 200,
		0xFFFFFF, "SPHERE = 2");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 250,
		0xFFFFFF, "CYLINDER = 3");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 300,
		0xFFFFFF, "CONE = 4");
}

void 	print_create_menu2(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 50,
		0xAAFFFF, "-- RT CREATE MODE --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 100,
		0xFFFFFF, "-- CHOOSE YOUR COLOR --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 150,
		0x00FFFF, "BLUE = 1");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 200,
		0xFF0000, "RED = 2");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 250,
		0x00FF00, "GREEN = 3");
}


void	print_help_mouvement(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 450,
		0xFFFFFF, "MOUVEMENT :");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 500,
		0xFFFFFF, "Translate : W, A, S, D");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 550,
		0xFFFFFF, "Rotate : UP, LEFT, DOWN, RIGHT");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 600,
		0xFFFFFF, "Lift : Q, E");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 650,
		0xFFFFFF, "Pivot : Z, X");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 700,
		0xFFFFFF, "COPY / PASTE OBJECT : LMB");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 550, 750,
		0xFFFFFF, "DELETE OBJECT: RMB");
}

void	print_help(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 50,
		0xAAFFFF, "-- RT HELP MODE --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 100,
		0xFFFFFF, "PIXELISATION : SPACE");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 150,
		0xFFFFFF, "EDIT MODE : ENTER");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 200,
		0xFFFFFF, "ANTI-ALIASING : R");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 250,
		0xFFFFFF, "STEREOSCOPIC : P");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 300,
		0xFFFFFF, "AMBIENT OCCLUSION : T");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 350,
		0xFFFFFF, "CEL-SHADING : C");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 400,
		0xFFFFFF, "FILTER : 0, 1, 2, 3, 4...");
	print_help_mouvement(e);
}

void	print_info(t_env *e)
{
	char *mode;

	if (!e->render_mode)
		mode = "Render mode : Nude";
	if (e->render_mode == 1)
		mode = "Render mode : Ambient Occlusion";
	if (e->render_mode == 2)
		mode = "Render mode : Stereoscopic";
	if (e->render_mode == 3)
		mode = "Render mode : Cel-Shading";
	if (e->pixelize)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 100,
		0xFFFFFF, "Pixelization : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 100,
		0xFFFFFF, "Pixelization : OFF");
	if (e->aa_flag)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 120,
		0xFFFFFF, "Anti-Aliasing : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 120,
		0xFFFFFF, "Anti-Aliasing : OFF");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 15, 140,
		0xFFFFFF, mode);
}
