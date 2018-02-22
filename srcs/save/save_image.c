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
	h_infos->plane = 1;
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
	write(fd, &h_infos.plane, 2);
	write(fd, &h_infos.bpp, 2);
	write(fd, &h_infos.compression, 4);
	write(fd, &h_infos.image_size, 4);
	write(fd, &h_infos.x_res, 4);
	write(fd, &h_infos.y_res, 4);
	write(fd, &h_infos.nb_color, 4);
	write(fd, &h_infos.important_color, 4);
}

char	*ft_strjoin_fre(char **s1, char **s2, int b1, int b2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2));
	i = 0;
	j = 0;
	while ((*s1) && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	if ((*s1) && b1)
		free(*s1);
	while ((*s2) && (*s2)[j])
	{
		str[i] = (*s2)[j];
		j++;
		i++;
	}
	if ((*s2) && b2)
		free(*s2);
	return (str);
}

void get_time_extend(char **name, struct tm *tm)
{
	char *tmp;

	tmp = ft_itoa(tm->tm_mon + 1);
	*name = ft_strjoin_fre(name , &tmp, 1, 1);
	tmp = ft_itoa(tm->tm_mday);
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
	tmp = ft_itoa(tm->tm_year + 1900);
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
	tmp = ft_strdup("_");
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
	tmp = ft_itoa(tm->tm_hour);
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
	tmp = ft_itoa(tm->tm_min);
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
	tmp = ft_itoa(tm->tm_sec);
	*name = ft_strjoin_fre(name, &tmp, 1, 1);
}

char			*get_time_to_str(int bl)
{
	char				*name;
	time_t				t;
	struct tm			*tm;
	char 				*tmp;

	t = time(NULL);
	tm = localtime(&t);
	if (bl == 1)
		name = ft_strdup("./save/screenshot/screenshot_");
	else
		name = ft_strdup("./save/sceneshot/sceneshot_");
	get_time_extend(&name, tm);
	if (bl == 1)
		tmp = ft_strdup(".bmp");
	else
		tmp = ft_strdup(".rt");
	name = ft_strjoin_fre(&name, &tmp, 1, 1);
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
	e->s_name = get_time_to_str(1);
	mkdir("./save/", 0777);
	mkdir("./save/screenshot/", 0777);
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
	free(e->s_name);
	return ;
}
