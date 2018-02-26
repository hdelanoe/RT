/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:00:25 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/07 16:22:50 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			free_content(t_json *member)
{
	t_json *tmp;

	while (member)
	{
		tmp = member;
		member = member->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}

double			get_content_from_member(char *name, t_json **membre)
{
	double		res;
	t_json		*tmp;

	res = 0;
	tmp = (*membre);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			res = ft_atod(tmp->content);
		tmp = tmp->next;
	}
	return (res);
}

t_vector		parse_point(t_json *membre)
{
	double x;
	double y;
	double z;

	x = get_content_from_member("x", &membre);
	y = get_content_from_member("y", &membre);
	z = get_content_from_member("z", &membre);
	free_content(membre);
	return (set_vector(x, y, z));
}

t_vector		parse_normal(t_json *membre)
{
	t_vector to_norm;

	to_norm = parse_point(membre);
	to_norm = normalize(&to_norm);
	return (to_norm);
}

t_color			parse_color(t_json *membre)
{
	double r;
	double g;
	double b;

	r = get_content_from_member("r", &membre);
	g = get_content_from_member("g", &membre);
	b = get_content_from_member("b", &membre);
	free_content(membre);
	return (set_color(b, g, r));
}
