/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:11:27 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:11:27 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_print_err(int argc)
{
	if (argc > 2)
		ft_putendl("The program can only run one scene at once.");
	if (argc < 2)
		ft_putendl("Please. Enter a scene to display");
	ft_help();
}

void	ft_help(void)
{
	ft_putendl("usage : ./rtv1 [scene]\n");
	ft_putendl("Scene instruction:\n");
	ft_putendl("Scene attributs: width, height, recursion and objects");
	ft_putendl("Objects name");
	ft_putendl("sphere, plane, cylinder, cone and light\n");
	ft_putendl("Each object as coord and color attribut");
	ft_putendl("sphere additionnal attributs : radius");
	ft_putendl("plane additionnal attributs : normal");
	ft_putendl("cylinder additionnal attributs : normal, radius, length");
	ft_putendl("cone additionnal attributs : tangent, length, axis");
	ft_putendl("Vector are set with x, y and z component");
	ft_putendl("Color are set with r, g and b component\n");
	ft_putendl("Each variable must be set like \"name\": \"value\"");
	ft_putendl("Each object must be set like \"object\": {component}");
	exit(EXIT_FAILURE);
}

void	ft_kill(char *text)
{
	ft_putendl(text);
	exit(EXIT_FAILURE);
}

int		proper_exit(t_env *e)
{
	mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int		check_keycode(int keycode, t_env *e)
{
	if (KC == KEY_ESCAPE)
		proper_exit(e);
	if (keycode == KEY_D || keycode == KEY_A || keycode == KEY_Q ||
		keycode == KEY_E || keycode == KEY_W || keycode == KEY_S ||
		keycode == KEY_UP || keycode == KEY_LEFT || keycode == KEY_DOWN ||
		keycode == KEY_RIGHT || keycode == KEY_Z || keycode == KEY_X ||
		keycode == KEY_SPACEBAR || keycode == KEY_R || keycode == KEY_T ||
		keycode == KEY_P || keycode == KEY_PAD_0 || keycode == KEY_PAD_1 ||
		keycode == KEY_PAD_2 || keycode == KEY_PAD_3 || keycode == KEY_PAD_4 ||
		keycode == KEY_PAD_5 || keycode == KEY_PAD_6 || keycode == KEY_ENTER ||
		keycode == KEY_H || keycode == KEY_PAD_ADD || keycode == KEY_I ||
		keycode == KEY_C || keycode == KEY_F || keycode == KEY_Y ||
		keycode == KEY_M || keycode == KEY_O || KC == KEY_L || KC == KEY_J ||
		keycode == KEY_U)
		return (1);
	return (0);
}
