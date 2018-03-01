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

#include "rt.h"

void	*ray_tracer_void(void *e)
{
	ray_tracer(e);
	return (NULL);
}

void	*pxl_tracer_void(void *e)
{
	if (((t_env*)e)->pixelize == 1)
		pxl_tracer(e, 6);
	else
		pxl_tracer(e, 18);
	return (NULL);
}

void	*pxl_tracer_vd2(void *e)
{
	pxl_tracer(e, 18);
	return (NULL);
}

void	ft_pthread(t_env *e, void *(*f)(void *param))
{
	t_env		tab[4];
	pthread_t	t[4];
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_env));
		tab[i].begin = e->height / 4 * i;
		tab[i].fin = e->height / 4 * (i + 1);
		tab[i].fin = i == 3 ? e->height : tab[i].fin;
		pthread_create(&t[i], NULL, f, &tab[i]);
		put_loading_bar(e, j++);
		i++;
	}
	while (i--)
	{
		pthread_join(t[i], NULL);
		put_loading_bar(e, j++);
	}
	e->loading = 1;
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->mlx.img_ptr, 0, 0);
}

void	ft_pthread_no_load(t_env *e, void *(*f)(void *param))
{
	t_env		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		ft_memcpy((void*)&tab[i], (void*)e, sizeof(t_env));
		tab[i].begin = e->height / 4 * i;
		tab[i].fin = e->height / 4 * (i + 1);
		tab[i].fin = i == 3 ? e->height : tab[i].fin;
		pthread_create(&t[i], NULL, f, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	e->loading = 1;
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
	e->mlx.img_ptr, 0, 0);
}
