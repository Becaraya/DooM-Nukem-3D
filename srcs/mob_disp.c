/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_disp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:03:33 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/23 18:39:12 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		mob_on_z(t_al *al, t_mob *e)
{
	e->posz += e->velz * al->dtime / 1000000;
	e->velz || e->posz != al->sec[e->csec].fl_hei ? e->on_ground = 0 : 0;
	if (!e->on_ground)
	{
		e->velz -= al->g * al->dtime / 1000000;
		if (e->posz < al->sec[e->csec].fl_hei)
		{
			e->posz = al->sec[e->csec].fl_hei;
			e->velz = 0;
			e->on_ground = 1;
		}
		if (e->posz + e->size > al->sec[e->csec].ce_hei)
		{
			e->posz = al->sec[e->csec].ce_hei - e->size;
			e->velz = 0;
		}
		if (al->sec[e->csec].ce_hei - al->sec[e->csec].fl_hei <
			e->size)
			e->alive = 0;
	}
}
