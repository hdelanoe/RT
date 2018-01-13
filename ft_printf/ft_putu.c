/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:34:36 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/20 12:23:28 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	accu_fld(t_ep *e, t_buff *buff)
{
	if ((size_t)e->accu > LEN(buff->er))
		ft_memset(buff->accu, '0', e->accu - LEN(buff->er));
	if ((size_t)e->fld > LEN(buff->er) + LEN(buff->accu))
	{
		ft_memset(buff->fld, ' ', e->fld - LEN(buff->er) - LEN(buff->accu));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - LEN(buff->er) - LEN(buff->accu));
	}
}

static void	ft_convert_arg(va_list arg, t_ep *e, t_buff *buff)
{
	if (e->flag[5] > 0)
	{
		if (e->flag[5] >= 2)
			buff->er = ft_llutoa((unsigned char)
					va_arg(arg, unsigned int), 10);
		else
			buff->er = ft_llutoa((unsigned short)
					va_arg(arg, unsigned int), 10);
	}
	else if (e->flag[6] >= 2)
		buff->er = ft_llutoa(va_arg(arg, unsigned long long), 10);
	else if (e->flag[6] == 1)
		buff->er = ft_llutoa(va_arg(arg, unsigned long), 10);
	else if (e->flag[7] >= 1)
		buff->er = ft_llutoa(va_arg(arg, uintmax_t), 10);
	else if (e->flag[8] >= 1)
		buff->er = ft_llutoa(va_arg(arg, size_t), 10);
	else
		buff->er = ft_utoa(va_arg(arg, unsigned int), 10);
}

static void	minus(t_ep *e, t_buff *buff)
{
	if (e->flag[0] > 0)
	{
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
		ft_putstr(buff->fld);
	}
	else
	{
		if (e->flag[2] == 0)
			ft_putstr(buff->fld);
		else
			ft_putstr(buff->fld);
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
	}
}

int			ft_putu(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;

	len = 0;
	if (c == 'U')
		buff->er = ft_llutoa(va_arg(arg, unsigned long), 10);
	else
		ft_convert_arg(arg, e, buff);
	if (buff->tmp)
	{
		ft_strdel(&buff->er);
		buff->er = buff->tmp;
	}
	if (e->flag[9] > 0 && ft_strcmp(buff->er, "0") == 0)
		buff->er = ft_strdup(NULL);
	accu_fld(e, buff);
	minus(e, buff);
	len += LEN(buff->er) + LEN(buff->fld) + LEN(buff->accu);
	ft_strdel(&buff->er);
	return (len);
}
