/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:58:44 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/20 18:01:37 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			ft_wlen(unsigned int w)
{
	int i;
	int sb;

	i = 1;
	sb = ft_size_bin(w);
	while (sb - 8 >= 0)
	{
		sb -= 8;
		i++;
	}
	return (i);
}

static int	how_to_put(t_ep *e, char *buff_fld, unsigned int w, int len)
{
	if (MB_CUR_MAX < 2 && w > 255)
		return (-1);
	if (e->flag[0] == 0)
		ft_putstr(buff_fld);
	if (w < 256)
		ft_putchar(w);
	else
		ft_putwchar(w);
	if (e->flag[0] > 0)
		ft_putstr(buff_fld);
	return (len);
}

int			ft_putc(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int				len;
	unsigned int	w;

	if (c == 'c' && (e->flag[6] == 0))
	{
		w = va_arg(arg, int);
		len = 1;
	}
	else
	{
		w = va_arg(arg, unsigned int);
		len = ft_wlen(w);
	}
	if (e->fld)
	{
		ft_memset(buff->fld, ' ', e->fld - len);
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - len);
	}
	if ((len = how_to_put(e, buff->fld, w, len)) < 0)
		return (-1);
	len += ft_strlen(buff->fld);
	return (len);
}
