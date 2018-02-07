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

double fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double grad(int hash, double x, double y, double z)
{
	int 	h;
	double 	u;
	double 	v;

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

double	perm(t_env *e, t_noise noise)
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

double 	noise(t_env *e, double x, double y, double z)
{
	 int i = (int)floor(x) & 255,                  
          j = (int)floor(y) & 255,                  
          k = (int)floor(z) & 255;
      x -= floor(x);                                
      y -= floor(y);                                
      z -= floor(z);
      double u = fade(x),                                
             v = fade(y),                                
             w = fade(z);
      int m = e->p[i  ]+j, mm = e->p[m]+k, mn = e->p[m+1]+k,      
          n = e->p[i+1]+j, nm = e->p[n]+k, nn = e->p[n+1]+k;   
 
      return lerp(w, lerp(v, lerp(u, grad(e->p[mm  ], x  , y  , z   ), 
                                     grad(e->p[nm  ], x-1, y  , z   )),
                             lerp(u, grad(e->p[mn  ], x  , y-1, z   ), 
                                     grad(e->p[nn  ], x-1, y-1, z   ))),
                     lerp(v, lerp(u, grad(e->p[mm+1], x  , y  , z-1 ), 
                                     grad(e->p[nm+1], x-1, y  , z-1 )), 
                             lerp(u, grad(e->p[mn+1], x  , y-1, z-1 ),
                                     grad(e->p[nn+1], x-1, y-1, z-1 ))));
}
