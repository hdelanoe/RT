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
	if (KC == KEY_D || KC == KEY_A || KC == KEY_Q || KC == KEY_E ||
		KC == KEY_W || KC == KEY_S || KC == KEY_UP || KC == KEY_LEFT ||
		KC == KEY_DOWN || KC == KEY_RIGHT || KC == KEY_Z || KC == KEY_X ||
		KC == KEY_SPACEBAR || KC == KEY_R || KC == KEY_T || KC == KEY_P ||
		KC == KEY_PAD_0 || KC == KEY_PAD_1 || KC == KEY_PAD_2 ||
		KC == KEY_PAD_3 || KC == KEY_PAD_4 ||
		KC == KEY_PAD_5 || KC == KEY_PAD_6 || KC == KEY_ENTER || KC == KEY_H
		|| KC == KEY_PAD_ADD || KC == KEY_C || KC == KEY_F || KC == KEY_Y)
		return (1);
	return (0);
}
