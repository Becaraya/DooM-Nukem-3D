/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/05 12:22:10 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		acceleration_entities(t_al *al, t_mob *mob)
{
/*	mob->velx = 0.50;
	mob->vely = 0.25;*/
	if (mob->posx < al->play.posx)
		mob->velx = 0.5;
	if (mob->posx > al->play.posx)
		mob->velx = -0.5;
	if (mob->posy < al->play.posy)
		mob->vely = 0.5;
	if (mob->posy > al->play.posy)
		mob->vely = -0.5;
	if (mob->posy < al->play.posy + 1 && mob->posy > al->play.posy - 1
		&& mob->posx < al->play.posx + 1 && mob->posx > al->play.posx - 1)
	{
		mob->alive = 0;
		mob->vely = 0;
		mob->velx = 0;
	}
	//mob->dir = 8192 / ( + 1)

//	mob->velx = al->sin[mob->dir] * mob->gd_vel;
//	mob->vely = al->cos[mob->dir] * mob->gd_vel;
}
