/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 19:30:08 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 19:14:28 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	minus(t_ep *e, t_buff *buff, char *plus)
{
	if (e->flag[0] > 0)
	{
		ft_putstr(plus);
		ft_putstr(buff->er);
	}
	ft_putstr(buff->fld);
	if (e->flag[0] == 0)
	{
		ft_putstr(plus);
		ft_putstr(buff->er);
	}
}

int			ft_putf(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;
	char	*plus;

	plus = NULL;
	if (e->accu == 0)
		e->accu = 6;
	if (c == 'F')
		buff->er = ft_ftoa(va_arg(arg, double), e->accu);
	else
		buff->er = ft_ftoa(va_arg(arg, double), e->accu);
	if (e->flag[1] > 0 && buff->er[0] != '-')
		plus = "+";
	if ((size_t)e->fld > ft_strlen(buff->er))
	{
		ft_memset(buff->fld, ' ', e->fld - ft_strlen(buff->er));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - ft_strlen(buff->er));
	}
	minus(e, buff, plus);
	len = ft_strlen(buff->er) + ft_strlen(buff->fld);
	ft_strdel(&buff->er);
	return (len);
}
