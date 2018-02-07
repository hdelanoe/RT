/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permtab.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 20:37:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/07 20:37:33 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERMTAB_H
# define PERMTAB_H
# include "rtv1.h"

typedef struct s_noise t_noise;

struct s_noise
{
	int 	i;
	int 	j;
	int 	k;
	double	x;
	double	y;
	double	z;
	double	u;
	double 	v;
	double 	w;
	int 	m;
	int		mm;
	int		mn;
	int 	n;
	int		nm;
	int		nn;
};

#endif
