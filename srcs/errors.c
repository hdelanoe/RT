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
