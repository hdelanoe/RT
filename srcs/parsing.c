/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 16:52:29 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_object(t_env *e, t_json *json)
{
	t_json *tmp;

	tmp = json->member;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, "sphere")))
			create_sphere(e, tmp);
		else if (!(ft_strcmp(tmp->name, "plane")))
			create_plane(e, tmp);
		else if (!(ft_strcmp(tmp->name, "cylinder")))
			create_cylinder(e, tmp);
		else if (!(ft_strcmp(tmp->name, "cone")))
			create_cone(e, tmp);
		else if (!(ft_strcmp(tmp->name, "light")))
			create_light(e, tmp);
		else
		{
			A
			exit_parser(1);
		}
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

void	create_tree(t_env *e, char **str)
{
	t_json	*json;

	if (str)
	{
		json = new_object();
		json->name = ft_strdup("scene");
		create_object(json, (*str), 0);
		get_object(e, json);
		ft_strdel(str);
	}
}

int			parsing(t_env *e, char *src_file)
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
	create_tree(e, &p.stock);
	return (p.j);
}
