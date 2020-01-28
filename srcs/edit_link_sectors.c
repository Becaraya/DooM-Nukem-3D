/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_link_sectors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:22:57 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 11:32:29 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	link_wall(t_sector *cur, t_walls *set, int id)
{
	t_walls		*wall;

	wall = cur->walls;
	while (wall)
	{
		if ((wall->x1 == set->x1 && wall->x2 == set->x2 && wall->y1 == set->y1
			&& wall->y2 == set->y2) ||
			(wall->x1 == set->x2 && wall->x2 == set->x1 && wall->y1 == set->y2
				&& wall->y2 == set->y1))
		{
			set->sec_lnk = id + 1;
			set->is_cross = 1;
			set->wall_tex = 0;
			return ;
		}
		wall = wall->next;
	}
}

static void	link_sector(t_sector *root, t_sector *cur, unsigned id)
{
	t_walls		*wall;
	unsigned	i;

	i = 0;
	while (root)
	{
		wall = (i != id ? cur->walls : 0);
		while (wall)
		{
			link_wall(root, wall, i);
			wall = wall->next;
		}
		root = root->next;
		i++;
	}
}

void		link_sectors(t_al *al)
{
	t_sector	*cur;
	unsigned	id;

	cur = al->sect;
	id = 0;
	while (cur)
	{
		link_sector(al->sect, cur, id);
		cur = cur->next;
		id++;
	}
}
