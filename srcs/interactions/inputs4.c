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
	if (keycode == KEY_PAD_ADD)
		e->pet += 5;
	else if (keycode == KEY_PAD_EQUAL && e->strechx <= 60)
		e->strechx *= 1.5;
	else if (keycode == KEY_PAD_DIVIDE && e->strechx >= 0.15)
		e->strechx *= 0.75;
	else if (keycode == KEY_PAD_MULTIPLY && e->strechy <= 2)
		e->strechy *= 1.1;
	else if (keycode == KEY_PAD_SUB && e->strechy >= 0.15)
		e->strechy *= 0.9;
}