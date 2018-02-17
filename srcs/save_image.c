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

static void create_header(t_env*e, t_header *header, t_infos *h_infos)
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

static void write_header(const int fd, t_header header, t_infos h_infos)
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


// void    write_info_header(t_env *e, int fd)
// {
//   int   header_size;
//   int   img_x;
//   int   img_y;
//   short nb_plane;
//   int   img_size;
// //  int   nb_color;
//   short   bpp;
 
//  printf("%s\n", "LOLL");
//   bpp = 24;
//   img_x = WIN_X;
//   img_y = WIN_Y;
//   header_size = 40;
//   nb_plane = 1;
//   img_size = (e->width * e->height) * 4;
//   // nb_color = 0;
//   write(fd, &header_size, 4);
//   write(fd, &img_x, 4);
//   write(fd, &img_y, 4);
//   write(fd, &nb_plane, 2);
//   write(fd, &bpp, 2);
//   write(fd, "\0\0\0\0", 4);
//   write(fd, &img_size, 4);
//   write(fd, 0, 4);
//   write(fd, 0, 4);
//   write(fd, 0, 4);
//   write(fd, 0, 4);
// }
// void    write_header(t_env *e, int fd) /* called first */
// {
//   int   fsize;
//   int   data_start;
 
//   fsize = 54 + (e->width * e->height) * 4;
//   data_start = 54;
//   write(fd, "BM", 2);
//   write(fd, &fsize, 4);
//   write(fd, "\0\0\0\0", 4);
//   write(fd, &data_start, 4);
//   write_info_header(e,fd);
// }
char *get_time_to_str(int bl)
{
    time_t now;
    struct tm *timeinfo;
    char *str;
    if (bl == 1)
        str = ft_strdup("tmp/screen_shot/");
    else 
      str = ft_strdup("tmp/scenes/");
    time(&now);
    timeinfo = localtime(&now);
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_mday));
    str = ft_strjoin(str, "-");
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_mon + 1));
    str = ft_strjoin(str, "-");
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_year + 1900));
    str = ft_strjoin(str, "_");
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_hour));
    str = ft_strjoin(str, ":");
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_min));
    str = ft_strjoin(str, ":");
    str = ft_strjoin(str, ft_itoa(timeinfo->tm_sec));
    return (str);
}
void ft_swap(unsigned char *a, unsigned char *b)
{
    unsigned char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void save_image(t_env *e)
{
    int fd;
    int y;
    int x;
    t_header  header;
    t_infos   h_infos;
  //  char *name;

    y = WIN_Y;
  //  name = ft_strjoin(get_time_to_str(1), ".bmp");
    if(!(fd = open("test.bmp", O_CREAT | O_TRUNC | O_WRONLY, 0666)))
    {
        printf("failed to open img\n");
        return ;
    }
    create_header(e, &header, &h_infos);
    write_header(fd, header, h_infos);
  //  write_header(e, fd);
    while (y > 0)
    {
        x = 0;
        while (x < WIN_X)
        {
            write(fd, &e->mlx.data[(((y * WIN_X) + x) * 4)], 3);
            x++;
        }
        y--;
    }
    close(fd);
    // ft_printf("Screen Shot done. Path : %s\n", name);
    return ;
}