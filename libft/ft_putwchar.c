/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:18:01 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/13 18:40:47 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	put_2o(unsigned int w)
{
	unsigned int	mask;
	unsigned char	res;
	t_octet			octet;

	mask = 49280;
	octet.d = (w << 26) >> 26;
	octet.u = ((w >> 6) << 27) >> 27;
	res = (mask >> 8) | octet.u;
	write(1, &res, 1);
	res = ((mask << 24) >> 24) | octet.d;
	write(1, &res, 1);
}

static void	put_3o(unsigned int w)
{
	unsigned int	mask;
	unsigned char	res;
	t_octet			octet;

	mask = 14712960;
	octet.t = (w << 26) >> 26;
	octet.d = ((w >> 6) << 26) >> 26;
	octet.u = ((w >> 12) << 28) >> 28;
	res = (mask >> 16) | octet.u;
	write(1, &res, 1);
	res = ((mask << 16) >> 24) | octet.d;
	write(1, &res, 1);
	res = ((mask << 24) >> 24) | octet.t;
	write(1, &res, 1);
}

static void	put_4o(unsigned int w)
{
	unsigned int	mask;
	unsigned char	res;
	t_octet			octet;

	mask = 4034953344;
	octet.q = (w << 26) >> 26;
	octet.t = ((w >> 6) << 26) >> 26;
	octet.d = ((w >> 12) << 26) >> 26;
	octet.u = ((w >> 18) << 29) >> 29;
	res = (mask >> 24) | octet.u;
	write(1, &res, 1);
	res = ((mask << 8) >> 24) | octet.d;
	write(1, &res, 1);
	res = ((mask << 16) >> 24) | octet.t;
	write(1, &res, 1);
	res = ((mask << 24) >> 24) | octet.q;
	write(1, &res, 1);
}

void		ft_putwchar(unsigned int w)
{
	unsigned int	value;
	int				size;

	value = w;
	size = ft_size_bin(w);
	if (size <= 7)
		write(1, &w, 1);
	else if (size <= 11)
		put_2o(value);
	else if (size <= 16)
		put_3o(value);
	else
		put_4o(value);
}
