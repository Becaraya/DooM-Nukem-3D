/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:11:26 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/20 14:40:09 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** et ouai bb c'est a la norme ça
*/

static void														flyyyy(t_al *al)
{
	al->play.velz -= al->g * al->dtime / 1000000;
	al->play.fly ? al->play.velz += (1000 / al->play.mass) * al->dtime / 1000000
	: 0;
}

void															game(t_al *al)
{
	rotate(al);
	al->k.space ? jump(al) : 0;
	if (al->play.on_ground)
		acceleration(al);
	else
		flyyyy(al);
//	if (al->ent[0].alive)
//		acceleration_entities(al, &al->ent[0]);
	displacement(al);
	render(al);
	SDL_WarpMouseInWindow(al->sdlwin, WIN_SIZEX / 2, WIN_SIZEY / 2);
	SDL_ShowCursor(SDL_DISABLE);
}
