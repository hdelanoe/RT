/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 14:37:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 09:58:19 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	minus(t_ep *e, char *buff_fld)
{
	if (e->flag[0] > 0)
		ft_putchar('%');
	ft_putstr(buff_fld);
	if (e->flag[0] == 0)
		ft_putchar('%');
}

int			ft_putmod(t_ep *e, t_buff *buff)
{
	int		len;

	len = 0;
	if (e->fld)
	{
		ft_memset(buff->fld, ' ', e->fld - 1);
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - 1);
	}
	minus(e, buff->fld);
	len += 1 + ft_strlen(buff->fld);
	return (len);
}
