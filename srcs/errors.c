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
	ft_putendl("\t\t\t\t\t\t\t\tScene instruction:\n");
	ft_putstr("'S' for sphere -> ");
	ft_putstr("Separated by tabulation enter the xPos, yPos, zPos, radius ");
	ft_putendl("and normalized red, green, blue, alpha colors.\n");
	ft_putstr("'L' for Light -> ");
	ft_putstr("Separated by tabulation enter the xPos, yPos, zPos ");
	ft_putendl("and normalized red, green, blue, alpha colors.\n");
	ft_putstr("'C' for Cylinder -> ");
	ft_putendl("Separated by tabulation enter the xPos, yPos, zPos, radius\n");
	ft_putstr("'K' for Cone -> ");
	ft_putendl("Separated by tabulation enter the xPos, yPos, zPos\n");
	ft_putstr("'P' for Plan -> ");
	ft_putstr("Separated by tabulation enter the xPos, yPos, zPos");
	ft_putendl(" and normalized Red, Green, Blue and Alpha colors.");
	exit(EXIT_FAILURE);
}

void	ft_kill(char *text)
{
	ft_putendl(text);
	exit(EXIT_FAILURE);
}
