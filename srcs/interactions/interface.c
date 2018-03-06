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

#include "../includes/rt.h"

void	print_help_mouvement(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 15, 0xAAFFFF, "MOUVEMENT :");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 16, 0xFFFFFF, "Translate : W, A, S, D");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 17, 0xFFFFFF, "Rotate : UP, LEFT, DOWN, RIGHT");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 19, 0xFFFFFF, "Lift : Q, E");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 20, 0xFFFFFF, "Pivot : Z, X");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 21, 0xFFFFFF, "COPY / PASTE OBJECT : LMB");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 23, 0xFFFFFF, "DELETE OBJECT: RMB");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 24, 0xAAFFFF, "SAVE / IMPORT :");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 25, 0xFFFFFF, "SAVE IMAGE : O");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 26, 0xFFFFFF, "SAVE SCENE : J");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 27, 0xFFFFFF, "LOAD OBJECT : K");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 28, 0xFFFFFF, "LOAD SCENE : L");
}

void	print_help(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30, 0xAAFFFF, "-- RT HELP MODE --");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 2, 0xFFFFFF, "PIXELISATION : SPACE");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 3, 0xFFFFFF, "EDIT MODE : ENTER");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 4, 0xFFFFFF, "ANTI-ALIASING : R");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 5, 0xFFFFFF, "STEREOSCOPIC : P");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 6, 0xFFFFFF, "AMBIENT OCCLUSION : T");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 7, 0xFFFFFF, "CEL-SHADING : C");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 8, 0xFFFFFF, "RANDOM PERLIN : M");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 9, 0xFFFFFF, "REMOVE AMBIENT : I");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 10, 0xFFFFFF, "ADD RECURSION : U");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 11, 0xFFFFFF, "STRECH TEXTURE : '=', '/'");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 12, 0xFFFFFF, "ROTATE TEXTURE : '-' / '+'");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->height / 50,
		e->height / 30 * 13, 0xFFFFFF, "FILTER : 0, 1, 2, 3, 4...");
	print_help_mouvement(e);
}

void	print_info(t_env *e)
{
	char *mode;

	if (!e->render_mode)
		mode = "Render mode : Nude";
	if (e->render_mode == 1)
		mode = "Render mode : Ambient Occlusion";
	mode = e->render_mode == 2 ? "Render mode : Stereoscopic" : mode;
	mode = e->render_mode == 3 ? "Render mode : Cel-Shading" : mode;
	if (e->pixelize == 1)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
			e->height / 30, 0xFFFFFF, "Pixelization : ON");
	else if (e->pixelize == 2)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
			e->height / 30, 0xFFFFFF, "Pixelization : TURBO");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
			e->height / 30, 0xFFFFFF, "Pixelization : OFF");
	if (e->aa_flag)
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
			e->height / 30 * 2, 0xFFFFFF, "Anti-Aliasing : ON");
	else
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
			e->height / 30 * 2, 0xFFFFFF, "Anti-Aliasing : OFF");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->width / 50,
		e->height / 30 * 3, 0xFFFFFF, mode);
}
