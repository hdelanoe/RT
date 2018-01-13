/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:54:24 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/20 12:23:16 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	accu_fld(t_ep *e, t_buff *buff, char *o)
{
	if ((size_t)e->accu > LEN(buff->er) + LEN(o))
		ft_memset(buff->accu, '0', e->accu - LEN(buff->er) - LEN(o));
	if ((size_t)e->fld > LEN(buff->er) + LEN(o) + LEN(buff->accu))
	{
		ft_memset(buff->fld, ' ', e->fld - LEN(buff->er)
				- LEN(o) - LEN(buff->accu));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - LEN(buff->er)
					- LEN(o) - LEN(buff->accu));
	}
}

static void	ft_convert_arg(va_list arg, t_ep *e, t_buff *buff)
{
	if (e->flag[5] > 0)
	{
		if (e->flag[5] >= 2)
			buff->er = ft_llutoa((unsigned char)
					va_arg(arg, unsigned int), 8);
		else
			buff->er = ft_llutoa((unsigned short)
					va_arg(arg, unsigned int), 8);
	}
	else if (e->flag[6] >= 2)
		buff->er = ft_llutoa(va_arg(arg, unsigned long long), 8);
	else if (e->flag[6] == 1)
		buff->er = ft_llutoa(va_arg(arg, unsigned long), 8);
	else if (e->flag[7] >= 1)
		buff->er = ft_llutoa(va_arg(arg, uintmax_t), 8);
	else if (e->flag[8] >= 1)
		buff->er = ft_llutoa(va_arg(arg, size_t), 8);
	else
		buff->er = ft_utoa(va_arg(arg, unsigned int), 8);
}

static void	minus(t_ep *e, t_buff *buff, char *o)
{
	if (e->flag[0] > 0)
	{
		ft_putstr(o);
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
		ft_putstr(buff->fld);
	}
	else
	{
		if (e->flag[2] == 0)
		{
			ft_putstr(buff->fld);
			ft_putstr(o);
		}
		else
		{
			ft_putstr(o);
			ft_putstr(buff->fld);
		}
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
	}
	ft_strdel(&buff->er);
}

int			ft_puto(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;
	char	*o;

	len = 0;
	if (c == 'O')
		buff->er = ft_llutoa(va_arg(arg, unsigned long), 8);
	else
		ft_convert_arg(arg, e, buff);
	if (e->flag[9] > 0 && ft_strcmp(buff->er, "0") == 0)
		buff->er = ft_strdup(NULL);
	if (buff->tmp)
	{
		ft_strdel(&buff->er);
		buff->er = ft_strdup(buff->tmp);
	}
	o = (e->flag[3] > 0 && ft_strcmp(buff->er, "0") != 0) ? "0" : NULL;
	accu_fld(e, buff, o);
	len += LEN(buff->er) + LEN(buff->fld) + LEN(o) + LEN(buff->accu);
	minus(e, buff, o);
	return (len);
}
