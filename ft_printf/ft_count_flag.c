/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 12:36:01 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/15 13:00:55 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prec(char *fmt, t_ep *e)
{
	int i;
	int j;

	i = 0;
	if (fmt[i] == '.')
	{
		e->flag[9]++;
		i++;
		j = 0;
		while (ft_isdigit(fmt[i]) == 1)
		{
			e->tab_accu[j] = fmt[i];
			i++;
			j++;
		}
		if (j)
			e->accu = ft_atoi(e->tab_accu);
	}
	while (ft_isflag(fmt[i]) < 10)
	{
		e->flag[ft_isflag(fmt[i])]++;
		i++;
	}
	return (i);
}

int		ft_count_flag(char *fmt, t_ep *e, va_list arg)
{
	int j;
	int i;

	i = 0;
	while (ft_isflag(fmt[i]) < 5)
	{
		e->flag[ft_isflag(fmt[i])]++;
		i++;
	}
	j = 0;
	if (fmt[i] == '*')
	{
		e->fld = va_arg(arg, int);
		i++;
	}
	while (ft_isdigit(fmt[i]) == 1)
	{
		e->tab_fld[j] = fmt[i];
		i++;
		j++;
	}
	if (j)
		e->fld = ft_atoi(e->tab_fld);
	i += prec(&fmt[i], e);
	return (i);
}

int		ft_isflag(char c)
{
	int	flag;

	flag = 10;
	if (c == '-')
		flag = 0;
	if (c == '+')
		flag = 1;
	if (c == '0')
		flag = 2;
	if (c == '#')
		flag = 3;
	if (c == ' ')
		flag = 4;
	if (c == 'h')
		flag = 5;
	if (c == 'l')
		flag = 6;
	if (c == 'j')
		flag = 7;
	if (c == 'z')
		flag = 8;
	if (c == '.')
		flag = 9;
	return (flag);
}

int		ft_isconv(char c)
{
	char	*s;
	int		i;

	s = "dDioOuUxXfFeEgGaAcsSbn%";
	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}
