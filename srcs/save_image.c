/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:08:58 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/17 14:08:59 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		create_header(t_env *e, t_header *header, t_infos *h_infos)
{
	header->type[0] = 0x42;
	header->type[1] = 0x4D;
	header->file_size = 54 + (int)(e->width * e->height) * 3;
	header->reserved = 0x00000000;
	header->offset = 54;
	h_infos->header_size = 40;
	h_infos->height = (int)e->height;
	h_infos->width = (int)e->width;
	h_infos->panes = 1;
	h_infos->bpp = 24;
	h_infos->compression = 0;
	h_infos->image_size = (int)(e->width * e->height) * 3;
	h_infos->x_res = 2835;
	h_infos->y_res = 2835;
	h_infos->nb_color = 0;
	h_infos->important_color = 0;
}

static void		write_header(const int fd, t_header header, t_infos h_infos)
{
	write(fd, &header.type, 2);
	write(fd, &header.file_size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &h_infos.header_size, 4);
	write(fd, &h_infos.width, 4);
	write(fd, &h_infos.height, 4);
	write(fd, &h_infos.panes, 2);
	write(fd, &h_infos.bpp, 2);
	write(fd, &h_infos.compression, 4);
	write(fd, &h_infos.image_size, 4);
	write(fd, &h_infos.x_res, 4);
	write(fd, &h_infos.y_res, 4);
	write(fd, &h_infos.nb_color, 4);
	write(fd, &h_infos.important_color, 4);
}

char			*get_time_to_str(void)
{
	char				*name;
	time_t				t;
	struct tm			*tm;

	t = time(NULL);
	tm = localtime(&t);
	name = ft_strjoin("screenshot_", ft_itoa(tm->tm_mon + 1));
	name = ft_strjoin(name, ft_itoa(tm->tm_mday));
	name = ft_strjoin(name, ft_itoa(tm->tm_year + 1900));
	name = ft_strjoin(name, "_");
	name = ft_strjoin(name, ft_itoa(tm->tm_hour));
	name = ft_strjoin(name, ft_itoa(tm->tm_min));
	name = ft_strjoin(name, ft_itoa(tm->tm_sec));
	name = ft_strjoin(name, ".bmp");
	return (name);
}

void			ft_swap(unsigned char *a, unsigned char *b)
{
	unsigned char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void			save_image(t_env *e)
{
	int				fd;
	int				y;
	int				x;
	t_header		header;
	t_infos			h_infos;

	y = WIN_Y;
	e->s_name = get_time_to_str();
	if (!(fd = open(e->s_name, O_CREAT | O_TRUNC | O_WRONLY, 0666)))
		ft_kill("something is went with screenshot");
	create_header(e, &header, &h_infos);
	write_header(fd, header, h_infos);
	while (y > 0)
	{
		x = 0;
		while (x < WIN_X)
			write(fd, &e->mlx.data[(((y * WIN_X) + x++) * 4)], 3);
		y--;
	}
	close(fd);
	ft_printf("Screenshot has been saved on path : %s\n", e->s_name);
	return ;
}
