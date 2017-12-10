/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_object(t_object *object, t_json *json)
{
	t_json *tmp;

	tmp = json->member;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, "sphere")))
			create_sphere(object, tmp);
		else if (!(ft_strcmp(tmp->name, "plane")))
			create_plane(object, tmp);
		else if (!(ft_strcmp(tmp->name, "cylinder")))
			create_cylinder(object, tmp);
		else if (!(ft_strcmp(tmp->name, "cone")))
			create_cone(object, tmp);
		else if (!(ft_strcmp(tmp->name, "light")))
			create_light(object, tmp);
		tmp = tmp->next;
	}
}

int			create_object(t_json *object, char *str, int i)
{
	int		j;
	t_json *tmp;

	object->member = new_object();
	tmp = object->member;
	char_is_valid(str[i], '{');
	while (str[++i] && str[i] != '}')
	{
		if (str[i] == '"')
		{
			j = 1;
			while (str[i + j] != str[i])
					j++;
			object->member->name = ft_strsub(&str[i + 1], 0, j - 1);
			i += j + 1;
			char_is_valid(str[i], ':');
			while (!(str[i] == '"' || str[i] == '{'))
				i++;
			if (str[i] == '{')
				i = create_object(object->member, str, i);
			else
			{
				j = 1;
				while (str[i + j] != str[i])
					j++;
				object->member->content = ft_strsub(&str[i + 1], 0, j - 1);
				i += j + 1;
			}
			if (str[i] == ',')
			{
				object->member->next = new_object();
				object->member = object->member->next;
			}
		}	
	}
	object->member = tmp;
	char_is_valid(str[i], '}');
	return (i + 1);
}

int			parsing(t_object *object, char *src_file)
{
	t_parsing p;

	if ((p.fd = open(src_file, O_RDONLY)) < 0)
		ft_kill("This file doesn't exist or bad typography.");
	p.j = 0;
	while ((p.i = read(p.fd, p.buff, BUF_SIZ)) != 0)
	{
		if (p.j == 0)
		{
			p.stock = ft_strdup(p.buff);
			p.j = 1;
		}
		else
		{
			p.tmp = p.stock;
			p.stock = ft_strjoin(p.tmp, p.buff);
			ft_strdel(&p.tmp);
		}
	}
	close(p.fd);
	parse(object, &p.stock);
	return (p.j);
}
