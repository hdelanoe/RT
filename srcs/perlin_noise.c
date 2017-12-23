/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:05:30 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/23 16:52:29 by nobila           ###   ########.fr       */
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
	int h;
	double u;
	double v;

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
 
double noise(double x, double y, double z) {
      int i = (int)floor(x) & 255,                  
          j = (int)floor(y) & 255,                  
          k = (int)floor(z) & 255;
      x -= floor(x);                                
      y -= floor(y);                                
      z -= floor(z);
      double u = fade(x),                                
             v = fade(y),                                
             w = fade(z);
      int m = p[i  ]+j, mm = p[m]+k, mn = p[m+1]+k,      
          n = p[i+1]+j, nm = p[n]+k, nn = p[n+1]+k;   
 
      return lerp(w, lerp(v, lerp(u, grad(p[mm  ], x  , y  , z   ), 
                                     grad(p[nm  ], x-1, y  , z   )),
                             lerp(u, grad(p[mn  ], x  , y-1, z   ), 
                                     grad(p[nn  ], x-1, y-1, z   ))),
                     lerp(v, lerp(u, grad(p[mm+1], x  , y  , z-1 ), 
                                     grad(p[nm+1], x-1, y  , z-1 )), 
                             lerp(u, grad(p[mn+1], x  , y-1, z-1 ),
                                     grad(p[nn+1], x-1, y-1, z-1 ))));
   }
 
void loadPermutation(void) {
	FILE* fp = fopen("perm_test.txt","r");
	int permutation[256],i;
 
	for(i=0;i<256;i++)
		fscanf(fp,"%d",&permutation[i]);
 
	fclose(fp);
 
	for (int i=0; i < 256 ; i++) p[256+i] = p[i] = permutation[i];
}