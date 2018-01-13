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

	if (!(json = (t_json*)malloc(sizeof(t_json))))
		exit_rt(1);
	json->name = NULL;
	json->content = NULL;
	json->member = NULL;
	json->next = NULL;
	return (json);
}

void	char_is_valid(char a, char b, char *str)
{
	if (a != b)
	{
		ft_putchar('*');
		ft_putchar(a);
		ft_putchar('*');
		ft_putendl(str);
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

int		get_content(char **content, char *str, int i)
{
	int j;

	j = 1;
	while (str[i + j] && str[i + j] != str[i])
		j++;
	if (str[i + j] == str[i])
		(*content) = ft_strsub(&str[i + 1], 0, j - 1);
	else
		exit_rt(1);
//	printf("%s\n", (*content));
	return (j);
}
