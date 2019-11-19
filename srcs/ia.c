/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/18 16:54:11 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		acceleration_entities(t_al *al)
{
	t_entity *ent;

	ent = (&al->ent[0]);
	ent->velx = 0.50;
	ent->vely = 0.25;
	//printf("%d\n", ent->csec);
	/*if (ent->px < al->play.posx)
		ent->velx = 1;
	if (ent->px > al->play.posx)
		ent->velx = -1;
	if (ent->py < al->play.posy)
		ent->vely = 1;
	if (ent->py > al->play.posy)
		ent->vely = -1;
	if (ent->py < al->play.posy + 1 && ent->py > al->play.posy -1 && ent->px < al->play.posx + 1 && ent->px > al->play.posx - 1)
	{	
		ent->etat = 0;
		ent->vely = 0;
		ent->velx = 0;
	}*/
	//ent->dir = 8192 / ( + 1)
	 
	//ent->velx = al->sin[ent->dir] * ent->gd_vel;
	//ent->vely = al->cos[ent->dir] * ent->gd_vel;
	
}