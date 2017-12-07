/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:49:35 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/05/25 17:29:01 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100

typedef struct		s_stock
{
	int				ret;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	char			*save;
	char			*rest;
}					t_stock;

int					get_next_line(int fd, char **line);

#endif
