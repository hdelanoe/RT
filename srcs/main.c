/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:52:24 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	exit_rt(int flag)
{
	if (flag == 1)
	{
		ft_putendl("Error in malloc");
		exit(1);
	}
}

void		display_window(t_env *env)
{
	env->mlx.mlx_ptr = mlx_init();
	env->mlx.win_ptr = mlx_new_window(env->mlx.mlx_ptr, WIN_X, WIN_Y, "RTv1");
	env->mlx.img_ptr = mlx_new_image(env->mlx.mlx_ptr, WIN_X, WIN_Y);
	env->mlx.data = (unsigned char*)mlx_get_data_addr(env->mlx.img_ptr,
		&env->mlx.bpp, &env->mlx.l_size, &env->mlx.endian);
	init_camera(env);
	camera_transformation(env);
	ray_tracer(env);
	mlx_hook(env->mlx.win_ptr, 2, (1L << 0), key_functions, env);
	mlx_hook(env->mlx.win_ptr, 17, (1L << 17), proper_exit, env);
	mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr, env->mlx.img_ptr, 0, 0);
	mlx_loop(env->mlx.mlx_ptr);
	mlx_destroy_window(env->mlx.mlx_ptr, env->mlx.win_ptr);
}

int			main(int argc, char **argv)
{
	t_env	*e;
	int		ret;

	loadPermutation();
	ret = 0;

	if (!(e = (t_env*)ft_memalloc(sizeof(t_env))))
		exit_rt(1);
	if (!(e->object = (t_object*)ft_memalloc(sizeof(t_object))))
		exit_rt(1);
	e->object->next = NULL;
	if (!(e->light = (t_light*)ft_memalloc(sizeof(t_light))))
		exit_rt(1);
	e->light->next = NULL;
	e->pixelize = 0;
	if (argc != 2)
		ft_print_err(argc);
	ret = parsing(e, argv[1]);
	display_window(e);
	return (0);
}
