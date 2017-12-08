/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		display_window(t_object *object)
{
	t_mlx	mlx;
	t_datas	d;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_X, WIN_Y, "RTv1");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_X, WIN_Y);
	mlx.data = (unsigned char*)mlx_get_data_addr(mlx.img_ptr,
	&mlx.bpp, &mlx.l_size, &mlx.endian);
	draw(&d, &mlx, object);
	mlx_hook(mlx.win_ptr, 2, (1L << 0), key_functions, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
}

int			main(int argc, char **argv)
{
	t_object	*object;
	int			ret;

	ret = 0;
	if (!(object = (t_object*)ft_memalloc(sizeof(t_object))))
		return (0);
	if (argc != 2)
		ft_print_err(argc);
	ret = parsing(object, argv[1]);
	display_window(object);
	return (0);
}
