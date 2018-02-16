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

void	ft_pthread(t_env *e, void *(*f)(void *param))
{
	t_env		tab[10];
	pthread_t	t[10];
	int			i;
	// t_object	*tmp;

	i = 0;
	while (i < 10)
	{
		// printf("e = %p\n", e->mlx.img_ptr);
		 ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_env));
		// printf("tab[%d] = %p\n", i, tab[i].mlx.img_ptr);
		 // tmp = tab[i].object;
		 // while (tab[i].object)
		 // {
		 // 	tab[i].object->node = e->object->node;
		 // 	tab[i].object->node_normal = e->object->node_normal;
		 // 	e->object = e->object->next;
		 // 	tab[i].object = tab[i].object->next;
		 // }
		 // tab[i].object = tmp;
	//	printf("i = %d\n", i);
		// init_camera(tab[i]);
		tab[i].begin = 100 * i;
		tab[i].fin = 100 * (i + 1);
	//	tab[i].object = test;
		pthread_create(&t[i], NULL, f, &tab[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
}
