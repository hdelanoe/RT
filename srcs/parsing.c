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
	int		id;
	t_json	*tmp;

	id = 0;
	while (json->member)
	{
		if (!(ft_strcmp(json->member->name, "sphere")))
			create_sphere(e, json->member, &id);
		else if (!(ft_strcmp(json->member->name, "plane")))
			create_plane(e, json->member, &id);
		else if (!(ft_strcmp(json->member->name, "cylinder")))
			create_cylinder(e, json->member, &id);
		else if (!(ft_strcmp(json->member->name, "cone")))
			create_cone(e, json->member, &id);
		else if (!(ft_strcmp(json->member->name, "light")))
			create_light(e, json->member);
		else
		{
			A
			exit_parser(1);
		tmp = json->member;
		json->member = json->member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
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
		free_json(json);
	}
	else
		exit_parser(1);
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
	free(p.stock);
	return (p.j);
}
