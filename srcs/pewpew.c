/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pewpew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/24 12:24:24 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		pewpew(t_al *al)
{
	unsigned	i;
	t_rc_ray	ray;

	ft_bzero(&ray, sizeof(t_rc_hit));
	cast_ray(al, al->play.dir, &ray);
	i = 0;
	while (i < ray.nb_hits)
	{
		if (ray.hits[i].is_entity)
			if (ray.hits[i].ent.alive)
			{
				al->ent[ray.hits[i].ent.index].alive = 0;
				if (al->ent[ray.hits[i].ent.index].alive)
				{
					al->ent[ray.hits[i].ent.index].velx = 20 * al->sin[al->play.dir];
					al->ent[ray.hits[i].ent.index].vely = 20 * al->cos[al->play.dir];
					al->ent[ray.hits[i].ent.index].velz = 2;
				}
				return ;
			}
		i++;
	}
}
