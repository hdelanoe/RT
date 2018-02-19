/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 20:37:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/07 20:37:33 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H
# include "rtv1.h"

typedef struct s_noise	t_noise;
typedef struct s_perlin	t_perlin;

struct	s_noise
{
	int					i;
	int					j;
	int					k;
	double				x;
	double				y;
	double				z;
	double				u;
	double				v;
	double				w;
	int					m;
	int					mm;
	int					mn;
	int					n;
	int					nm;
	int					nn;
};

struct	s_perlin
{
	double				a;
	double				b;
	double				c;
	double				d;
	double				e;
};

#endif
