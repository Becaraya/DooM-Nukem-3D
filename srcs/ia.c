/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:06:05 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/19 13:09:46 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		acceleration_entities(t_al *al)
{
	(void)al; // pour enlever le warning, a retirer apres
/*	t_entity *ent;

	ent = (&al->ent[0]);
	if (ent->posx < al->play.posx)
		ent->velx = 1;
	if (ent->posx > al->play.posx)
		ent->velx = -1;
	if (ent->posy < al->play.posy)
		ent->vely = 1;
	if (ent->posy > al->play.posy)
		ent->vely = -1;
	if (ent->posy < al->play.posy + 1 && ent->posy > al->play.posy -1 && ent->posx < al->play.posx + 1 && ent->posx > al->play.posx - 1)
	{	
		ent->etat = 0;
		ent->vely = 0;
		ent->velx = 0;
	}
	//ent->dir = 8192 / ( + 1)
	 
	//ent->velx = al->sin[ent->dir] * ent->gd_vel;
	//ent->vely = al->cos[ent->dir] * ent->gd_vel;
	*/	
}