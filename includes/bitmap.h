/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 19:51:54 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/23 19:51:55 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H
# include "rt.h"

typedef struct			s_header
{
	char				type[2];
	int					reserved;
	int					file_size;
	int					offset;
}						t_header;

typedef struct			s_infos
{
	int					header_size;
	int					image_size;
	int					nb_color;
	int					important_color;
	int					compression;
	int					width;
	int					height;
	int					x_res;
	int					y_res;
	int					plane;
	short				bpp;
}						t_infos;

#endif