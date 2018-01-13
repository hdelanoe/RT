/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 19:33:09 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 20:15:41 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

unsigned int	adrlen(unsigned long adr)
{
	int i;

	i = 3;
	while (adr / 16 > 0)
	{
		adr /= 16;
		i++;
	}
	return (i);
}

static char		*solve_addr(unsigned long adr, char *base, int i, char *res)
{
	while ((adr / 16) > 0)
	{
		res[i] = base[(adr % 16)];
		adr /= 16;
		i--;
	}
	res[i] = base[(adr % 16)];
	i--;
	while (i > 0)
	{
		res[i] = '0';
		i--;
	}
	res[1] = 'x';
	res[0] = '0';
	return (res);
}

char			*ft_putaddress(void *p, t_ep *e)
{
	unsigned long	adr;
	int				i;
	char			*res;
	char			*base;

	adr = (unsigned long)p;
	if (adrlen(adr) > (unsigned int)e->accu)
	{
		if (e->accu == 0 && e->flag[9] > 0)
			i = adrlen(adr) - 1;
		else
			i = adrlen(adr);
	}
	else
		i = e->accu + 2;
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	i--;
	base = "0123456789abcdef";
	return (solve_addr(adr, base, i, res));
}

int				ft_putp(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int		len;

	len = 0;
	if (c == 'p')
		buff->er = ft_putaddress(va_arg(arg, void*), e);
	if ((size_t)e->fld > ft_strlen(buff->er))
	{
		ft_memset(buff->fld, ' ', e->fld - ft_strlen(buff->er));
		if (e->flag[2] > 0 && e->flag[0] == 0 && !e->accu)
			ft_memset(buff->fld, '0', e->fld - ft_strlen(buff->er));
	}
	if (e->flag[0] > 0)
		ft_putstr(buff->er);
	ft_putstr(buff->fld);
	if (e->flag[0] == 0)
		ft_putstr(buff->er);
	len += ft_strlen(buff->er) + ft_strlen(buff->fld);
	ft_strdel(&buff->er);
	return (len);
}
