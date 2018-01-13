/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 11:23:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/20 15:35:33 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	accu_fld(t_ep *e, t_buff *buff, char *sign)
{
	if ((size_t)e->accu > LEN(buff->er))
		ft_memset(buff->accu, '0', e->accu - LEN(buff->er));
	if ((size_t)e->fld > LEN(buff->er) + LEN(sign) + LEN(buff->accu))
	{
		ft_memset(buff->fld, ' ', e->fld - LEN(buff->er)
				- LEN(sign) - LEN(buff->accu));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - LEN(buff->er)
					- LEN(sign) - LEN(buff->accu));
	}
}

static void	ft_convert_arg(va_list arg, t_ep *e, int s, t_buff *buff)
{
	if (e->flag[5] >= 2)
	{
		if (!(s = (char)va_arg(arg, int)))
			buff->tmp = ft_strdup("0");
		else if (ft_strcmp((buff->er = ft_itoa(s)), "128") == 0)
			buff->tmp = ft_strdup("-128");
	}
	else if (e->flag[5] == 1)
	{
		if (!(s = (short)va_arg(arg, int)))
			buff->tmp = ft_strdup("0");
		else if (ft_strcmp((buff->er = ft_itoa(s)), "32768") == 0)
			buff->tmp = ft_strdup("-32768");
	}
	else if (e->flag[6] >= 2)
		buff->er = ft_lltoa(va_arg(arg, long long));
	else if (e->flag[6] == 1)
		buff->er = ft_lltoa(va_arg(arg, long));
	else if (e->flag[7] >= 1)
		buff->er = ft_lltoa(va_arg(arg, intmax_t));
	else if (e->flag[8] >= 1)
		buff->er = ft_lltoa(va_arg(arg, size_t));
	else
		buff->er = ft_itoa(va_arg(arg, int));
}

static void	minus(t_ep *e, t_buff *buff, char *sign)
{
	if (e->flag[0] > 0)
	{
		ft_putstr(sign);
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
		ft_putstr(buff->fld);
	}
	else
	{
		if (e->flag[2] == 0)
		{
			ft_putstr(buff->fld);
			ft_putstr(sign);
		}
		else
		{
			ft_putstr(sign);
			ft_putstr(buff->fld);
		}
		ft_putstr(buff->accu);
		ft_putstr(buff->er);
	}
}

static char	*ft_sign(t_ep *e, t_buff *buff)
{
	int		neg;
	char	*sign;
	int		i;

	neg = 0;
	i = 0;
	sign = NULL;
	if (buff->er[i] == '-')
	{
		while (buff->er[i])
		{
			buff->er[i] = buff->er[i + 1];
			i++;
		}
		neg = 1;
	}
	if (e->flag[9] > 0 && ft_strcmp(buff->er, "0") == 0)
		ft_strdel(&buff->er);
	if (neg == 1)
		sign = "-";
	else if (e->flag[1] > 0)
		sign = "+";
	else if (e->flag[4] > 0)
		sign = " ";
	return (sign);
}

int			ft_putd(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;
	char	*sign;
	int		s;

	s = 0;
	len = 0;
	if (c == 'd' || c == 'i')
		ft_convert_arg(arg, e, s, buff);
	else
		buff->er = ft_lltoa(va_arg(arg, long));
	if (buff->tmp)
	{
		ft_strdel(&buff->er);
		buff->er = buff->tmp;
	}
	sign = ft_sign(e, buff);
	accu_fld(e, buff, sign);
	minus(e, buff, sign);
	len += LEN(buff->er) + LEN(buff->fld) + LEN(sign) + LEN(buff->accu);
	ft_strdel(&buff->er);
	return (len);
}
