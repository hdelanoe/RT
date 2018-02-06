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

void	ft_pthread(t_env *e, void *(*f)(void *param))
{
	t_env		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		 ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_env));
	//	printf("i = %d\n", i);
		// init_camera(tab[i]);
		tab[i].begin = 200 * i;
		tab[i].fin = 200 * (i + 1);
	//	printf("tab[%d] = %d\n", i, tab[i].begin);
		pthread_create(&t[i], NULL, f, &tab[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
}
