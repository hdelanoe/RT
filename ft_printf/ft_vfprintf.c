/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 02:16:06 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/21 14:55:27 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	set_zero(t_ep *e, t_buff *buff)
{
	e->flag[0] = 0;
	e->flag[1] = 0;
	e->flag[2] = 0;
	e->flag[3] = 0;
	e->flag[4] = 0;
	e->flag[5] = 0;
	e->flag[6] = 0;
	e->flag[7] = 0;
	e->flag[8] = 0;
	e->flag[9] = 0;
	ft_bzero(e->tab_fld, 320);
	ft_bzero(e->tab_accu, 320);
	e->fld = 0;
	e->accu = 0;
	ft_bzero(buff->fld, 320);
	ft_bzero(buff->accu, 320);
	buff->tmp = NULL;
	buff->er = NULL;
	buff->wer = NULL;
}

int			is_color(char c)
{
	if (c == 'R' || c == 'G' || c == 'Y' || c == 'M' || c == 'C'
			|| c == 'I' || c == 'S' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

void		color(char *fmt, t_ep *e)
{
	if (fmt[e->i] == '{' && is_color(fmt[e->i + 1]) && fmt[e->i + 2] == '}')
	{
		if (fmt[e->i + 1] == 'R')
			ft_putstr("\x1B[91m");
		else if (fmt[e->i + 1] == 'G')
			ft_putstr("\x1B[92m");
		else if (fmt[e->i + 1] == 'Y')
			ft_putstr("\x1B[93m");
		else if (fmt[e->i + 1] == 'M')
			ft_putstr("\x1B[95m");
		else if (fmt[e->i + 1] == 'C')
			ft_putstr("\x1B[96m");
		else if (fmt[e->i + 1] == 'I')
			ft_putstr("\x1B[3m");
		else if (fmt[e->i + 1] == 'S')
			ft_putstr("\x1B[4m");
		else if (fmt[e->i + 1] == 'E')
			ft_putstr("\x1B[0m");
		e->i += 2;
	}
	else
	{
		ft_putchar(fmt[e->i]);
		e->len++;
	}
}

static int	how_to_put(char *fmt, va_list arg, t_ep *e, t_buff *buff)
{
	while (fmt[e->i] != '\0')
	{
		set_zero(e, buff);
		if (fmt[e->i] == '%')
		{
			e->i++;
			e->i += ft_count_flag(&fmt[e->i], e, arg);
			if ((e->conv = ft_convert(fmt[e->i], arg, e, buff)) < 0)
				return (-1);
			else if (e->conv == 0 && !ft_isconv(fmt[e->i]))
				e->i--;
			else
				e->len += e->conv;
		}
		else
			color(fmt, e);
		e->i++;
	}
	return (e->len);
}

int			ft_vfprintf(char *fmt, va_list arg)
{
	t_ep	e;
	t_buff	buff;
	int		len;

	e.len = 0;
	e.i = 0;
	if (ft_strcmp(fmt, "%") == 0)
		return (0);
	if ((len = how_to_put(fmt, arg, &e, &buff)) < 0)
		return (-1);
	return (len);
}
