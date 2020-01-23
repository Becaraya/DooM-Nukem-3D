/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/23 16:11:54 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		acceleration_entities(t_al *al, t_mob *mob)
{
	double d;

	mob->velx = (mob->posx < al->play.posx) ? 0.25 : -0.25;
	mob->vely = (mob->posy < al->play.posy) ? 0.25 : -0.25;
	d = ((mob->posx - al->play.posx) * (mob->posx - al->play.posx) +
		(mob->posy - al->play.posy) * (mob->posy - al->play.posy));
	if (d < 2.8
		&& mob->posz + mob->size >= al->play.posz
		&& mob->posz <= al->play.posz + al->play.size)
	{
		al->play.velz = (d <= 2) ? 0 : 2.5;
		al->play.velx = (mob->posx < al->play.posx) ? 2.5 : -2.5;
		al->play.vely = (mob->posy < al->play.posy) ? 2.5 : -2.5;
		mob->velx = (mob->posx < al->play.posx) ? -2.5 : 2.5;
		mob->vely = (mob->posy < al->play.posy) ? -2.5 : 2.5;
		mob->velx = (d < 2.5) ? 0 : mob->velx;
		mob->vely = (d < 2.5) ? 0 : mob->vely;
		if (mob->hit) 
		al->play.alive -= (al->play.alive - al->hard < 0) ? al->play.alive : al->hard;
		mob->hit = 0;
	}
	else
		mob->hit = 1;
}
