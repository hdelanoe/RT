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

void	ft_delete_obj_lst(t_object **beg_obj)
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

t_light	*ft_remove_light_begin(t_light **prev, t_light **ptr)
{
	t_light *begin_object;

	*prev = NULL;
	begin_object = (*ptr)->next;
	free((*ptr)->type);
	free(*ptr);
	*ptr = begin_object;
	return (begin_object);
}

void	ft_delete_light_lst(t_light **beg_obj)
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

int		check_existance(char *text, t_env *e)
{
	if (parsing(e, text))
	{
		ft_delete_obj_lst(&e->object);
		ft_delete_light_lst(&e->light);
		ft_printf("Chargement de la scene...\n");
		default_env(e);
		create_tree(e, &e->stock);
		ft_strdel(&e->stock);
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		e->loading = 0;
		e->mlx.mlx_ptr = NULL;
		display_window(e);
		return (1);
	}
	return (0);
}

int		read_scene_files(t_env *e)
{
	char	*tmp;

	ft_printf("\nListe des scenes :\n\n");
	if (!print_list_scenes("scenes", "."))
		return (0);
	ft_printf("\nEntrez une scene a charger :\n");
	if (get_next_line(fileno(stdin), &e->argv_cpy) == 1)
	{
		if (!e->argv_cpy[0])
			return (0);
		tmp = ft_strdup("./scenes/");
		e->argv_cpy = ft_strjoin_fre(&tmp, &e->argv_cpy, 1, 1);
		if (!check_existance(e->argv_cpy, e))
		{
			ft_strdel(&e->argv_cpy);
			return (0);
		}
		ft_strdel(&e->argv_cpy);
	}
	else
		ft_printf("Error input scene");
	if (e->copy)
		e->copy = NULL;
	return (1);
}
