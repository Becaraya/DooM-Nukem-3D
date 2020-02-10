/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:11:26 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/06 15:00:49 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** et ouai bb c'est a la norme ça
*/

static void													flyyyy(t_al *al)
{
	al->play.velz -= al->g * al->dtime / 1000000;
	al->play.fly ? al->play.velz += (1000 / al->play.mass) * al->dtime / 1000000
	: 0;
}

static void													sp_key(t_al *al)
{
	double		tmp;

	if (al->door != 0)
	{
		tmp = 0.000001 * al->dtime;
		if (al->k.lbrack)
		{
			al->sec[al->door].fl_hei + tmp < al->sec[al->door].ce_hei ?
			al->sec[al->door].fl_hei += tmp : 0;
		}
		else if (al->k.rbrack)
			al->sec[al->door].fl_hei -= tmp;
	}
}

void														game(t_al *al)
{
	rotate(al);
	sp_key(al);
	al->k.space ? jump(al) : 0;
	al->play.on_ground ? acceleration(al) : flyyyy(al);
	displacement(al);
	render(al);
	if (al->play.won)
	{
		al->status = WON;
		pix_to_pix(al->pix, al->pix_dead, 1);
		SDL_ShowCursor(SDL_ENABLE);
	}
	else if (al->play.alive)
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
