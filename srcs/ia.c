/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/22 19:01:07 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		acceleration_entities(t_al *al, t_mob *mob)
{
	double d;

	mob->velx = (mob->posx < al->play.posx)? 0.25 : -0.25;
	mob->vely = (mob->posy < al->play.posy)? 0.25 : -0.25;
	d = ( (mob->posx -al->play.posx) * (mob->posx -al->play.posx) +
		(mob->posy - al->play.posy) * (mob->posy - al->play.posy));
	if (d < 2.8
		&& mob->posz + mob->size >= al->play.posz 
		&& mob->posz <= al->play.posz + al->play.size)
	{
		al->play.velz = (d <= 2)? 0 : 2.5;
		al->play.velx = (mob->posx < al->play.posx)? 2.5 : -2.5;
		al->play.vely = (mob->posy < al->play.posy)? 2.5 : -2.5;
		mob->velx = (mob->posx < al->play.posx)? -2.5 : 2.5;
		mob->vely = (mob->posy < al->play.posy)?-2.5 : 2.5;
		if (d < 2.5)
			mob->velx = 0;
		if (d < 2.5)
			mob->vely = 0;
		if (mob->hit)
			al->play.alive--;
		mob->hit = 0; 
	}
	else
		mob->hit = 1;
}
