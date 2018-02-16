/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/23 17:58:26 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	*ray_tracer_void(void *e) 
{
	ray_tracer(e);
	return (NULL);
}

void	*pxl_tracer_void(void *e) 
{
	pxl_tracer(e, 6);
	return (NULL);
}

void 	*stereo_tracer_void(void *e)
{
	stereo_tracer(e);
	return (NULL);
}

void 	*aa_tracer_void(void *e)
{
	aa_tracer(e, 1);
	return (NULL);
}

void	ft_pthread(t_env *e, void *(*f)(void *param))
{
	t_env		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		 ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_env));
		tab[i].begin = e->width / 4 * i;
		tab[i].fin = e->width / 4 * (i + 1);
		if (i == 3)
			tab[i].fin = e->width;
		pthread_create(&t[i], NULL, f, &tab[i]);
		i++;
	}
	i = -1;
	while (++i < 4)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
}
