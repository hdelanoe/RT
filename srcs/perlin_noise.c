/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:05:30 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/07 20:48:46 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double		lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double		grad(int hash, double x, double y, double z)
{
	int			h;
	double		u;
	double		v;

	h = hash & 15;
	u = h < 8 ? x : y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	if (h & 1)
		u *= -1;
	if (h & 2)
		v *= -1;
	return (u + v);
}

double  perm(t_env *e, t_noise noise)
{
  return (lerp(noise.w, lerp(noise.v, lerp(noise.u, 
        grad(e->p[noise.mm], noise.x, noise.y, noise.z), 
        grad(e->p[noise.nm], noise.x -1, noise.y, noise.z)),
      lerp(noise.u,
        grad(e->p[noise.mn], noise.x, noise.y -1, noise.z), 
        grad(e->p[noise.nn], noise.x -1, noise.y -1, noise.z))),
      lerp(noise.v, lerp(noise.u,
        grad(e->p[noise.mm +1], noise.x, noise.y, noise.z -1), 
        grad(e->p[noise.nm +1], noise.x -1, noise.y, noise.z -1)), 
      lerp(noise.u,
        grad(e->p[noise.mn +1], noise.x  , noise.y -1, noise.z -1),
      grad(e->p[noise.nn +1], noise.x -1, noise.y -1, noise.z -1)))));
}
 
double   noise(t_env *e, double x, double y, double z)
{
  t_noise n;
 
  n.i = (int)floor(x) & 255;                
    n.j = (int)floor(y) & 255;                  
    n.k = (int)floor(z) & 255;
    n.x = x -floor(x);                                
    n.y = y -floor(y);                                
    n.z = z -floor(z);                                
    n.u = fade(n.x);                            
    n.v = fade(n.y);                                
    n.w = fade(n.z);
    n.m = e->p[n.i] + n.j;
    n.mm = e->p[n.m]+ n.k, n.mn = e->p[n.m+1]+n.k;      
    n.n = e->p[n.i+1]+n.j, n.nm = e->p[n.n]+n.k, n.nn = e->p[n.n+1]+n.k;   
 
      return (perm(e, n));
}
