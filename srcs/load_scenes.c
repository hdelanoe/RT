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

#include "../includes/rtv1.h"

void		ft_delete_obj_lst(t_object **beg_obj)
{
	t_object *ptr;
	t_object *prev;

	ptr = *beg_obj;
	prev = NULL;
	while (ptr)
	{
		if (ptr == *beg_obj)
			*beg_obj = ft_remove_begin(&prev, &ptr);
		else
		{
			prev->next = ptr->next;
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
			free(ptr);
			ptr = prev->next;
		}
	}
}

void		check_existance(char *text, t_env *e)
{
	if (access(ft_strtrim(text), F_OK) != -1)
	{
		ft_delete_obj_lst(&e->object);
		ft_delete_light_lst(&e->light);
		ft_printf("Chargement de la scene...\n");
		parsing(e, ft_strtrim(text));
		ft_pthread(e, ray_tracer_void);
	}
	else
		ft_printf("This file doesn't exist. Loading scene aborted.\n");
}

void		read_scene_files(t_env *e)
{
	DIR				*p;
	struct dirent	*pp;
	int				len;

	p = opendir("./scenes/");
	ft_printf("\nListe des scenes :\n\n");
	if (p != NULL)
	{
		while ((pp = readdir(p)) != NULL)
		{
			len = ft_strlen(pp->d_name);
			if (ft_strncmp(pp->d_name + len - 3, ".rt", 3) == 0)
				ft_printf("%s\n", pp->d_name);
		}
	}
	ft_printf("\nEntrez une scene a changer :\n");
	fgets(e->argv_cpy, 300, stdin);
	e->argv_cpy = ft_strjoin("./scenes/", e->argv_cpy);
	check_existance(e->argv_cpy, e);
}
