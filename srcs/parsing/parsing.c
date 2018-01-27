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
	t_json	*tmp;

	while (json->member)
	{
		tmp = json->member;
		if (!(ft_strcmp(tmp->name, "sphere")) && tmp->member)
			create_sphere(e, tmp);
		else if (!(ft_strcmp(tmp->name, "plane")) && tmp->member)
			create_plane(e, tmp);
		else if (!(ft_strcmp(tmp->name, "triangle")) && tmp->member)
			create_triangle(e, tmp);
		else if (!(ft_strcmp(tmp->name, "quad")) && tmp->member)
			create_quad(e, tmp);
		else if (!(ft_strcmp(tmp->name, "cylinder")) && tmp->member)
			create_cylinder(e, tmp);
		else if (!(ft_strcmp(tmp->name, "cone")) && tmp->member)
			create_cone(e, tmp);
		else if (!(ft_strcmp(tmp->name, "light")) && tmp->member)
			create_light(e, tmp);
		else if (!(ft_strcmp(tmp->name, "disk")) && tmp->member)
			create_disk(e, tmp);
		else if (!(ft_strcmp(tmp->name, "torus")) && tmp->member)
			create_torus(e, tmp);
		else if (!(ft_strcmp(tmp->name, "glass")) && tmp->member)
			create_glass(e, tmp);
		else if (tmp->member)
			parse_scene(e, tmp);
		json->member = json->member->next;
		free_json_member(&tmp);
	}
}

void		add_new_member(t_json **list, t_json *new_member)
{
	t_json	*tmp;

	if (!(*list)->name)
	{
		free((*list));
		(*list) = new_member;
		return ;
	}
	tmp = (*list);
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_member;
	(*list) = tmp;

}

int			create_object(t_json *object, char *str, int i)
{
	t_json *member;

	object->member = new_object();
	while (str[++i] && str[i] != '}')
	{
		if (str[i] == '"')
		{
			member = new_object();
			 i += get_content(&member->name, str, i) + 1;
			char_is_valid(str[i], ':', &str[i]);
			while (str[i] && !(str[i] == '"' || str[i] == '{'))
				i++;
			if (str[i] == '{')
				i = create_object(member, str, i);
			else
				i += get_content(&member->content, str, i);
			add_new_member(&object->member, member);
		}	
	}
	char_is_valid(str[i], '}', &str[i]);
	return (i);
}

void	create_tree(t_env *e, char **str)
{
	t_json	*json;

	if ((*str)[0] == '{')
	{
		json = new_object();
		create_object(json, (*str), 0);
		get_object(e, json);
	}
	else
		exit_parser(1);
}

int		parsing(t_env *e, char *src_file)
{
	t_parsing p;

	p.buff = ft_memalloc(sizeof(p.buff));
	p.stock = NULL;
	if ((p.fd = open(src_file, O_RDONLY)) < 0)
		ft_kill("This file doesn't exist or bad typography.");
	p.j = 0;

	while (get_next_line(p.fd, &p.buff) == 1)
	{
		p.j = 1;
		p.tmp = p.stock;
		p.stock = ft_strjoin(p.tmp, p.buff);
		ft_strdel(&p.tmp);
	}
	close(p.fd);
	if (p.i >= 0)
		create_tree(e, &p.stock);
	return (p.j);
}
