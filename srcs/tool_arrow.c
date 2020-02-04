/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:04:13 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/04 14:37:43 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		set_size_arrow(t_al *al, int i)
{
	if (i == 1 && al->play.size == 1.78)
	{
		al->play.size = 1.80;
		al->play.eyez = 1.65;
	}
	else if (i == 1)
	{
		al->play.size += 0.05;
		al->play.eyez += 0.05;
	}
	else if (i == -1 && al->play.size == 1.78)
	{
		al->play.size = 1.75;
		al->play.eyez = 1.60;
	}
	else
	{
		al->play.size -= 0.05;
		al->play.eyez -= 0.05;
	}
}

void			arrow_stat_player_minus(t_al *al)
{
	if (al->edit.stat == LIFE && al->play.alive > 2)
		al->play.alive--;
	if (al->edit.stat == POW && al->play.power_mult > 0.2)
		al->play.power_mult -= 0.1;
	if (al->edit.stat == SIZE && al->play.size > 0.3)
		set_size_arrow(al, -1);
	if (al->edit.stat == MASS && al->play.mass > 20 && al->play.mass != 67)
		al->play.mass -= 10;
	if (al->edit.stat == MASS && al->play.mass == 67)
		al->play.mass = 60;
}

void			arrow_stat_player_plus(t_al *al)
{
	if (al->edit.stat == LIFE && al->play.alive < 25)
		al->play.alive++;
	if (al->edit.stat == POW)
		al->play.power_mult += 0.1;
	if (al->edit.stat == SIZE)
		set_size_arrow(al, 1);
	if (al->edit.stat == MASS && al->play.mass != 67)
		al->play.mass += 10;
	if (al->edit.stat == MASS && al->play.mass == 67)
		al->play.mass = 70;
}
