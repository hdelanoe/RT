/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:20:59 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/20 18:35:55 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		put_type_object(char *type, int fd)
{
	char *tmp;
	char *tmp_2;

	tmp_2 = ft_strdup("\"");
	tmp = ft_strdup(type);
	tmp = ft_strjoin_fre(&tmp_2, &tmp, 1, 1);
	tmp_2 = ft_strdup("\": ");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

char		*check_color_value(double color)
{
	char *tmp;
	char *tmp_2;

	if (color < 1 && color > 0)
	{
		tmp = ft_strdup("0.");
		tmp_2 = ft_itoa(color * 10);
		tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	}
	else
		tmp = ft_itoa(color);
	return (tmp);
}

void		put_color(t_color *color, int fd)
{
	char *tmp;
	char *tmp_2;

	tmp = ft_strdup("\"color\": {\"r\": \"");
	tmp_2 = check_color_value(color->r);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"g\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = check_color_value(color->g);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"b\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = check_color_value(color->b);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\"}\n");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void		put_xyz(t_vector *point, int fd)
{
	char *tmp;
	char *tmp_2;

	tmp = ft_strdup("\"x\": \"");
	tmp_2 = ft_itoa(point->x);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"y\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_itoa(point->y);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\", \"z\": \"");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_itoa(point->z);
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	tmp_2 = ft_strdup("\"},\n");
	tmp = ft_strjoin_fre(&tmp, &tmp_2, 1, 1);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void		check_value_point(double *a)
{
	if (*a > 0.5)
		*a = 1;
	else if (*a < 0.5 && *a > 0)
		*a = 1;
	else if (*a < -0.5)
		*a = -1;
	else
		*a = 0;
}
