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
# include "rt.h"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>

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
	int						k;
	char					*buff;
	char					*stock;
	char					*tmp;
	char					*tmp_2;
	DIR						*directory;
	struct dirent			*name;
	char					**v[4096];
	char					**f[4096];
	t_vector				tmp1;
	t_vector				tmp2;
	t_vector				tmp3;

};

t_json						*new_object(void);
void						add(t_json **current, t_json *new);
void						char_is_valid(char a, char b);
int							create_object(t_json *object, char *str, int i);
double						get_content_from_member(char *name,
							t_json **membre);
int							get_content(char **content, char *str, int i);
void						free_json_member(t_json **member);
void						exit_parser(int flag);
void						ft_print_err(int argc);
void						ft_help(void);
void						ft_kill(char *text);
int							check_args(char *argv);
void						exit_rt(int flag);
t_vector					parse_point(t_json *membre);
t_vector					parse_normal(t_json *membre);
t_color						parse_color(t_json *membre);

#endif
