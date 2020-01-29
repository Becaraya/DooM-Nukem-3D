/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pewpew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/29 15:42:15 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		piou_piou(t_al *al, unsigned i, t_rc_ray ray)
{
	if ((int)al->ent[ray.hits[i].ent.index].alive < 0)
	{
		al->ent[ray.hits[i].ent.index].alive = 0;
		al->ent[ray.hits[i].ent.index].anim = 0;
	}
	if (al->ent[ray.hits[i].ent.index].alive)
	{
		al->ent[ray.hits[i].ent.index].velx = 20 * al->sin[al->play.dir];
		al->ent[ray.hits[i].ent.index].vely = 20 * al->cos[al->play.dir];
		if (al->ent[ray.hits[i].ent.index].posz ==
			al->sec[al->ent[ray.hits[i].ent.index].csec].fl_hei)
			al->ent[ray.hits[i].ent.index].velz = 2;
	}
}

void			pewpew(t_al *al)
{
	unsigned	i;
	t_rc_ray	ray;

	al->fire_anim = 0;
	ft_bzero(&ray, sizeof(t_rc_hit));
	cast_ray(al, al->play.dir, &ray);
	i = 0;
	while ((int)i < ray.nb_hits)
	{
		if (ray.hits[i].ent.alive && ray.hits[i].is_entity)
		{
			al->ent[ray.hits[i].ent.index].alive -= al->play.dmg;
			piou_piou(al, i, ray);
			return ;
		}
		i++;
	}
}
