/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 11:03:15 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/14 20:27:12 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		put_else(char c, t_ep *e, t_buff *buff)
{
	ft_memset(buff->fld, ' ', e->fld - 1);
	if (e->flag[2] > 0 && e->flag[0] == 0)
		ft_memset(buff->fld, '0', e->fld - 1);
	if (e->flag[0] > 0)
		ft_putchar(c);
	ft_putstr(buff->fld);
	if (e->flag[0] == 0)
		ft_putchar(c);
	return (e->fld);
}

int		ft_convert(char c, va_list arg, t_ep *e, t_buff *buff)
{
	int	len;

	len = 0;
	if (c == '%')
		len += ft_putmod(e, buff);
	else if (c == 's' || c == 'S')
		len += ft_puts(c, arg, e, buff);
	else if (c == 'p')
		len += ft_putp(c, arg, e, buff);
	else if (c == 'd' || c == 'D' || c == 'i')
		len += ft_putd(c, arg, e, buff);
	else if (c == 'o' || c == 'O')
		len += ft_puto(c, arg, e, buff);
	else if (c == 'u' || c == 'U')
		len += ft_putu(c, arg, e, buff);
	else if (c == 'x' || c == 'X')
		len += ft_putx(c, arg, e, buff);
	else if (c == 'c' || c == 'C')
		len += ft_putc(c, arg, e, buff);
	else if (c == 'f' || c == 'F')
		len += ft_putf(c, arg, e, buff);
	else if (e->fld)
		len += put_else(c, e, buff);
	return (len);
}
