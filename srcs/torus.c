// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   torus.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2017/11/28 14:09:37 by hdelanoe          #+#    #+#             */
// /*   Updated: 2017/11/28 14:09:39 by hdelanoe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "rtv1.h"

// t_torus		*add_new_torus(t_object *object, t_torus *new_torus)
// {
// 	t_torus	*tmp;

// 	tmp = object->start_torus;
// 	if (tmp)
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		new_torus->next = NULL;
// 		tmp->next = new_torus;
// 	}
// 	else
// 		object->start_torus = new_torus;
// 	return (tmp);
// }

// void		create_torus(t_object *object, char *line)
// {
// 	t_torus		*torus;
// 	int			i;

// 	torus = (t_torus*)ft_memalloc(sizeof(t_torus));
// 	object->tab_line = ft_strsplit(line, ' ');
// 	torus->center = set_vector(ft_atod(object->tab_line[1]), ft_atod(object->tab_line[2]), ft_atod(object->tab_line[3]));
// 	torus->big_radius = ft_atod(object->tab_line[4]);
// 	torus->small_radius = ft_atod(object->tab_line[5]);
// 	torus->axis = set_vector(ft_atod(object->tab_line[6]), ft_atod(object->tab_line[7]), ft_atod(object->tab_line[8]));
// 	torus->axis = normalize(&torus->axis);
// 	torus->color = set_color(ft_atod(object->tab_line[9]), ft_atod(object->tab_line[10]), ft_atod(object->tab_line[11]));
// 	torus->id = ft_atoi(object->tab_line[12]);
// 	i = 0;
// 	while (object->tab_line[i])
// 	{
// 		free(object->tab_line[i]);
// 		i++;
// 	}
// 	torus = add_new_torus(object, torus);
// }