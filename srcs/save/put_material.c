/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:50:07 by etranchi          #+#    #+#             */
/*   Updated: 2018/02/28 17:50:08 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	put_material(int fd, t_object *object)
{
	write(fd, "\t\t", 2);
	put_type_object("material", fd);
	write(fd, "{\n", 2);
	write(fd, "\t\t\t", 3);
	put_int("ambient", object->ambient, fd);
	write(fd, "\t\t\t", 3);
	put_int("diffuse", object->diffuse, fd);
	write(fd, "\t\t\t", 3);
	put_int("specular", object->specular, fd);
	write(fd, "\t\t\t", 3);
	put_int("reflect", object->reflect, fd);
	write(fd, "\t\t\t", 3);
	put_int("refract", object->refract, fd);
	write(fd, "\t\t\t", 3);
	put_int("absorbtion", object->absorbtion, fd);
	write(fd, "\t\t\t", 3);
	put_int("radius", object->radius, fd);
	write(fd, "\t\t\t", 3);
	put_int("texture", object->texture, fd);
	write(fd, "\t\t\t", 3);
	put_int("bump", object->bump, fd);
	write(fd, "\t\t\t", 3);
	put_double("indice", object->indice, fd);
	write(fd, "\n\t\t\t}\n", 6);
}
