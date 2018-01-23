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

void		display_window(t_env *e)
{
	e->mlx.mlx_ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.mlx_ptr, e->width, e->height, "RT");
	e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, e->width, e->height);
	if (!((e->mlx.pen = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/pen.xpm", &(e->mlx.l_size), &e->mlx.endian))))
		ft_kill("Texture error");
	e->mlx.data = (unsigned char*)mlx_get_data_addr(e->mlx.img_ptr,
		&e->mlx.bpp, &e->mlx.l_size, &e->mlx.endian);
	init_camera(e);
	camera_transformation(e);
	// init_stereo(e);
	ray_tracer(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
	mlx_hook(e->mlx.win_ptr, 2, (1L << 0), key_functions, e);
	mlx_hook(e->mlx.win_ptr, 17, (1L << 17), proper_exit, e);
	mlx_mouse_hook(e->mlx.win_ptr, mouse, e);
	mlx_loop(e->mlx.mlx_ptr);
	mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
}

t_env		*init(void)
{
	t_env *e;

	if (!(e = (t_env*)ft_memalloc(sizeof(t_env))))
		exit_rt(1);
	if (!(e->object = (t_object*)ft_memalloc(sizeof(t_object))))
		exit_rt(1);
	if (!(e->light = (t_light*)ft_memalloc(sizeof(t_light))))
		exit_rt(1);
	e->width = WIN_X;
	e->height = WIN_Y;
	e->distance = WIN_X;
	e->pixelize = 0;
	e->is_past = 0;
	e->is_copy = 0;
	e->lookat = set_vector(0, 0, 0);
	return (e);
}

int			main(int argc, char **argv)
{
	t_env	*e;
	int		ret;

	loadPermutation();
	ret = 0;
	e = init();
	
	if (argc != 2)
		ft_print_err(argc);
	ret = parsing(e, argv[1]);
	display_window(e);
	return (0);
}
