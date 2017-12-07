/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:26:09 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/12/07 17:26:10 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	exit_parser(int flag)
{
	if (flag == 1)
	{
		ft_putendl("This isn't a valid scene");
		exit(42);
	}
}

t_json	*new_object(void)
{
	t_json	*json;

	json = (t_json*)malloc(sizeof(t_json));
	json->name = NULL;
	json->content = NULL;
	json->member = NULL;
	json->next = NULL;
	return (json);
}

void	char_is_valid(char a, char b)
{
	if (a != b)
	{
		ft_putchar(a);
		exit_parser(1);
	}
}

void	add(t_json **current, t_json *new)
{
	t_json *tmp;

	tmp = (*current);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	parse(t_object *object, char **str)
{
	t_json	*json;

	if (str)
	{
		json = new_object();
		json->name = ft_strdup("scene");
		create_object(json, (*str), 0);
		get_object(object, json);
		ft_strdel(str);
	}
}
