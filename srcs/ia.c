/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/15 19:17:27 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		acceleration_entities(t_al *al, t_mob *mob)
{
/*	mob->velx = 0.50;
	mob->vely = 0.25;*/
	if (mob->posx < al->play.posx)
		mob->velx = 0.25;
	if (mob->posx > al->play.posx)
		mob->velx = -0.25;
	if (mob->posy < al->play.posy)
		mob->vely = 0.25;
	if (mob->posy > al->play.posy)
		mob->vely = -0.25;
	if (mob->posy < al->play.posy + 2 && mob->posy > al->play.posy - 2
	&& mob->posx < al->play.posx + 2 && mob->posx > al->play.posx - 2)
	{
		al->play.velz = 2.5;
		if (mob->posx < al->play.posx)
			mob->velx = -2.5;
		if (mob->posx < al->play.posx)
			al->play.velx = 2.5;
		if (mob->posx > al->play.posx)
			mob->velx = 2.5;
		if (mob->posx > al->play.posx)
			al->play.velx = -2.5;
		if (mob->posy < al->play.posy)
			mob->vely = -2.5;
		if (mob->posy < al->play.posy)
			al->play.vely = 2.5;
		if (mob->posy > al->play.posy)
			mob->vely = 2.5;
		if (mob->posy > al->play.posy)
			al->play.vely = -2.5;
		if (mob->hit)
		al->play.alive--;
		mob->hit = 0; 
	}
	else
	{
			mob->hit = 1;
	}
	
	//mob->dir = 8192 / ( + 1)

//	mob->velx = al->sin[mob->dir] * mob->gd_vel;
//	mob->vely = al->cos[mob->dir] * mob->gd_vel;
}
