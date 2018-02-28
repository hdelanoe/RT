/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:08:58 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/17 14:08:59 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		ft_delete_obj_lst(t_object **beg_obj)
{
	t_object *ptr;
	t_object *prev;

	ptr = *beg_obj;
	prev = NULL;
	while (ptr)
	{
		if (ptr->sub_object)
			ft_delete_obj_lst(&ptr->sub_object);
		if (ptr == *beg_obj)
			*beg_obj = ft_remove_begin(&prev, &ptr);
		else
		{
			prev->next = ptr->next;
			free(ptr->type);
			free(ptr);
			ptr = prev->next;
		}
	}
}

t_light		*ft_remove_light_begin(t_light **prev, t_light **ptr)
{
	t_light *begin_object;

	*prev = NULL;
	begin_object = (*ptr)->next;
	free((*ptr)->type);
	free(*ptr);
	*ptr = begin_object;
	return (begin_object);
}

void		ft_delete_light_lst(t_light **beg_obj)
{
	t_light *ptr;
	t_light *prev;

	ptr = *beg_obj;
	prev = NULL;
	while (ptr)
	{
		if (ptr == *beg_obj)
			*beg_obj = ft_remove_light_begin(&prev, &ptr);
		else
		{
			prev->next = ptr->next;
			free(ptr->type);
			free(ptr);
			ptr = prev->next;
		}
	}
}

void		check_existance(char *text, t_env *e)
{
	if (access(text, F_OK) != -1)
	{
		ft_delete_obj_lst(&e->object);
		ft_delete_light_lst(&e->light);
		ft_printf("Chargement de la scene...\n");
		default_env(e);
		parsing(e, text);
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		e->loading = 0;
		e->mlx.mlx_ptr = NULL;
		display_window(e);
	}
	else
	{
		ft_printf("This file doesn't exist. Loading scene aborted.\n");
	}
	free(e->argv_cpy);
}

void		read_scene_files(t_env *e)
{
	DIR				*p;
	struct dirent	*pp;
	char			*tmp;

	p = opendir("./scenes/");
	ft_printf("\nListe des scenes :\n\n");
	if (p != NULL)
	{
		while ((pp = readdir(p)) != NULL)
			ft_printf("%s\n", pp->d_name);
	}
	e->loading = 0;
	ft_printf("\nEntrez une scene a changer :\n");
	if (get_next_line(fileno(stdin), &e->argv_cpy) == 1)
	{
		tmp = ft_strdup("./scenes/");
		e->argv_cpy = ft_strjoin_fre(&tmp, &e->argv_cpy, 1, 1);
		check_existance(e->argv_cpy, e);
	}
	else
		ft_printf("Error input scene");
	closedir(p);
	if (e->copy)
		e->copy = NULL;
}
