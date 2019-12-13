/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:11:26 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 16:13:34 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** et ouai bb c'est a la norme ça
*/

static void														flyyyy(t_al *al)
{
	al->play.velz -= al->g * al->dtime / 1000000;
}

void															game(t_al *al)
{
	rotate(al);
	al->k.space ? jump(al) : 0;
	if (al->play.on_ground)
		acceleration(al);
	else
		flyyyy(al);
	if (al->ent[0].alive)
		acceleration_entities(al, al->ent[0]);
	displacement(al);
	render(al);
}
