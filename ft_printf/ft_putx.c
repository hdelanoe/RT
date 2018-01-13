/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:25:30 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/20 17:59:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	accu_fld(t_ep *e, t_buff *buff, char *ox)
{
	if ((size_t)e->accu > LEN(buff->er))
		ft_memset(buff->accu, '0', e->accu - LEN(buff->er));
	if ((size_t)e->fld > LEN(buff->er) + LEN(buff->accu))
	{
		ft_memset(buff->fld, ' ', e->fld - LEN(buff->er)
				- LEN(ox) - LEN(buff->accu));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - LEN(buff->er)
					- LEN(ox) - LEN(buff->accu));
	}
}

static void	minus(t_ep *e, t_buff *buff, char *ox)
{
	if (e->flag[0] > 0)
	{
		ft_putstr(ox);
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
		ft_putstr(buff->fld);
	}
	else
	{
		if (e->flag[2] == 0)
		{
			ft_putstr(buff->fld);
			ft_putstr(ox);
		}
		else
		{
			ft_putstr(ox);
			ft_putstr(buff->fld);
		}
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
	}
}

static void	ft_convert_arg(va_list arg, t_ep *e, int up, t_buff *buff)
{
	if (e->flag[5] >= 2)
	{
		if (e->flag[5] > 1)
			buff->er = ft_ltoa_base((unsigned char)
				va_arg(arg, unsigned int), 16, up);
		else
			buff->er = ft_ltoa_base((unsigned short)
				va_arg(arg, unsigned int), 16, up);
		if (!buff->er)
			buff->tmp = ft_strdup("0");
	}
	else if (e->flag[6] >= 2)
		buff->er = ft_ltoa_base(va_arg(arg, unsigned long long), 16, up);
	else if (e->flag[6] == 1)
		buff->er = ft_ltoa_base(va_arg(arg, unsigned long), 16, up);
	else if (e->flag[7] >= 1)
		buff->er = ft_ltoa_base(va_arg(arg, uintmax_t), 16, up);
	else if (e->flag[8] >= 1)
		buff->er = ft_ltoa_base(va_arg(arg, size_t), 16, up);
	else
		buff->er = ft_itoa_base(va_arg(arg, unsigned int), 16, up);
}

int			ft_putx(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;
	char	*ox;
	int		up;

	len = 0;
	ox = NULL;
	up = (c == 'X') ? 1 : 0;
	ft_convert_arg(arg, e, up, buff);
	if (e->flag[9] > 0 && ft_strcmp(buff->er, "0") == 0)
		buff->er = ft_strdup(NULL);
	else if (e->flag[3] > 0 && ft_strcmp(buff->er, "0") != 0)
	{
		ox = "0x";
		(up) ? ox = "0X" : NULL;
	}
	if (buff->tmp)
	{
		ft_strdel(&buff->er);
		buff->er = ft_strdup(buff->tmp);
	}
	accu_fld(e, buff, ox);
	minus(e, buff, ox);
	len += LEN(buff->er) + LEN(buff->fld) + LEN(ox) + LEN(buff->accu);
	ft_strdel(&buff->er);
	return (len);
}
