/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:33:15 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/21 15:23:54 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	accu_fld(t_ep *e, t_buff *buff)
{
	int rest;
	int	i;

	if ((rest = ft_strlen(buff->er)) == 0)
		rest = ft_strlen((char*)buff->wer);
	if (e->accu < rest && e->flag[9] > 0)
	{
		i = 0;
		while (i < e->accu)
		{
			buff->accu[i] = buff->er[i];
			i++;
		}
		rest = e->accu;
		buff->er = buff->accu;
	}
	else if (e->accu && buff->wer)
		rest = e->accu;
	if (e->fld > rest)
	{
		ft_memset(buff->fld, ' ', e->fld - rest);
		if (e->flag[2] > 0 && e->flag[0] == 0)
			ft_memset(buff->fld, '0', e->fld - rest);
	}
}

int			putws(t_ep *e, t_buff *buff, int len)
{
	if (MB_CUR_MAX > 1)
	{
		e->accu = (e->flag[9] == 0) ? 320 : e->accu;
		while (*buff->wer && len < e->accu)
		{
			ft_putwchar(*buff->wer);
			len += ft_wlen(*buff->wer);
			buff->wer++;
		}
	}
	else
		return (0);
	return (len);
}

static int	how_to_char(t_ep *e, t_buff *buff, char c)
{
	int len;

	len = 0;
	if (e->flag[9] > 0 && !e->accu)
		return (len);
	if (!buff->wer)
	{
		ft_putstr(buff->er);
		len += ft_strlen(buff->er);
	}
	else if (*buff->wer)
	{
		if ((len = putws(e, buff, len)) == 0)
			return (-1);
	}
	if (e->fld > e->accu && e->flag[9] > 0 && c == 'S')
		len = e->fld;
	return (len);
}

int			ft_puts(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;

	len = 0;
	if (e->flag[6] == 0 && c == 's')
		buff->er = va_arg(arg, char*);
	else
		buff->wer = va_arg(arg, unsigned int*);
	if (buff->er == NULL && e->flag[9] == 0)
		buff->er = "(null)";
	accu_fld(e, buff);
	if (e->flag[0] == 0 && (buff->er || !(MB_CUR_MAX > 1 && c == 'S')))
		ft_putstr(buff->fld);
	if ((len += how_to_char(e, buff, c)) == -1)
		return (-1);
	if (len != e->fld)
		len += ft_strlen(buff->fld);
	if (e->flag[0] > 0)
		ft_putstr(buff->fld);
	return (len);
}
