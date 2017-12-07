/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:35:54 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/30 13:35:56 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef XML_PARSER_H
# define XML_PARSER_H
# define BUF_SIZ 2
# define BALISE_SIZE 64
# define A printf("LOL\n");
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"

typedef struct		s_object
{
	t_sphere		*start_sphere;
	t_cylinder		*start_cylinder;
	t_plane			*start_plane;
	t_cone			*start_cone;
	t_light			*start_light;
	t_torus			*start_torus;
	char			**tab_line;
}					t_object;

typedef struct 	s_json
{
	char			*name;
	char			*content;
	struct s_json	*member;
	struct s_json	*next;
}				t_json;

void	exit_parser(int flag);
void	parse(t_object *object, char *str);
int		is_valid(char *str);
#endif