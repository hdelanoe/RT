/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:33:24 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/28 19:33:25 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	inputs4(int keycode, t_env *e)
{
	if (keycode == KEY_PAD_ADD && e->pet <= 1000)
		e->pet = e->pet + 5;
	if (keycode == KEY_PAD_SUB && e->pet >= 5)
		e->pet = e->pet - 5;
	else if (keycode == KEY_PAD_EQUAL && e->strechx <= 220)
		e->strechx += 5;
	else if (keycode == KEY_PAD_DIVIDE && e->strechx >= 5)
		e->strechx -= 5;
}
