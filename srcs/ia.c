/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/28 17:17:37 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		acceleration_entities(t_al *al,t_mob mob)
{
	t_mob *ent;

	ent = &mob;
	ent->velx = 0.50;
	ent->vely = 0.25;
	//printf("%f\n", ent->posx);
	if (ent->posx < al->play.posx)
		ent->velx = 1;
	if (ent->posx > al->play.posx)
		ent->velx = -1;
	if (ent->posy < al->play.posy)
		ent->vely = 1;
	if (ent->posy > al->play.posy)
		ent->vely = -1;
	if (ent->posy < al->play.posy + 1 && ent->posy > al->play.posy -1 
	&& ent->posx < al->play.posx + 1 && ent->posx > al->play.posx - 1)
	{	
		ent->alive = 0;
		ent->vely = 0;
		ent->velx = 0;
	}
	//ent->dir = 8192 / ( + 1)
	 
	//ent->velx = al->sin[ent->dir] * ent->gd_vel;
	//ent->vely = al->cos[ent->dir] * ent->gd_vel;	
}