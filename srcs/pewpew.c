/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pewpew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/23 18:34:14 by hutricot         ###   ########.fr       */
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
		{
			al->ent[ray.hits[i].ent.index].alive = 0;
			return ;
		}
		i++;
	}	
}