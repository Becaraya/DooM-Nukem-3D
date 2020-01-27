/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:11:26 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/27 16:10:01 by hutricot         ###   ########.fr       */
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


static void														sp_key(t_al *al)
{
	double tmp;

	tmp = 0.000001 * al->dtime; 
	if (al->k.lbrack && al->nb_sec >= 2)
	{
		al->sec[2].fl_hei + tmp < al->sec[2].ce_hei ? al->sec[2].fl_hei += tmp
		: 0;
	}
	else if (al->k.rbrack && al->nb_sec >= 2)
		al->sec[2].fl_hei -= tmp;

}
void															game(t_al *al)
{
	rotate(al);
	sp_key(al);
	al->k.space ? jump(al) : 0;
	if (al->play.on_ground)
		acceleration(al);
	else
		flyyyy(al);
	displacement(al);
	render(al);
	if (al->play.alive)
	{
		SDL_WarpMouseInWindow(al->sdlwin, WIN_SIZEX / 2, WIN_SIZEY / 2);
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		al->status = DEAD;
		pix_to_pix(al->pix, al->pix_dead, 1);
		SDL_ShowCursor(SDL_ENABLE);
	}
}
