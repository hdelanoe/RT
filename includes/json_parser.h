/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:35:54 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/30 13:35:56 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_H
# define JSON_PARSER_H
# include "../libft/libft.h"
# include "rtv1.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct s_json		t_json;
typedef struct s_parsing	t_parsing;

struct						s_json
{
	char					*name;
	char					*content;
	t_json					*member;
	t_json					*next;
};

struct						s_parsing
{
	int						fd;
	int						i;
	int						j;
	char					*buff;
	char					*stock;
	char					*tmp;
}; 
t_json						*new_object(void);
void						add(t_json **current, t_json *new);
void						char_is_valid(char a, char b, char *str);
int							create_object(t_json *object, char *str, int i);
double 						get_content_from_member(char *name, t_json **membre);
int							get_content(char **content, char *str, int i);
void						free_json_member(t_json **member);
#endif