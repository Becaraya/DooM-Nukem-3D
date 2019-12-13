/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:08:39 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/13 00:24:19 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void    		set_coo(t_al *al, t_point bev, int who, t_walls *wall)
{
    if (who == 1)
    {
        wall->x1 = bev.x - (bev.x % al->edit.zoom);
        wall->y1 = bev.y - (bev.y % al->edit.zoom);
    }
    else
    {
        wall->x2 = bev.x - (bev.x % al->edit.zoom);
        wall->y2 = bev.y - (bev.y % al->edit.zoom);
    }
}

void			init_sect(t_al *al, t_sector *sect)
{
	t_sector	*new;

	new = NULL;
	if (!sect)
	{
		if (!(al->sect = ft_memalloc(sizeof(t_sector))))
			yeet(al);
		ft_bzero(al->sect, sizeof(t_sector *));
		if (!(al->sect->walls = (t_walls *)ft_memalloc(sizeof(t_walls))))
			yeet(al);
		ft_bzero(al->sect->walls, sizeof(t_walls *));
		set_coo(al, itop(-1, -1), 1, al->sect->walls);
		set_coo(al, itop(-1, -1), 2, al->sect->walls);
		al->sect->next = NULL;
		al->sect->walls->next = NULL;
	}
	else
	{
		if (!(new = ft_memalloc(sizeof(t_sector))))
			yeet(al);
		if (!(new->walls = ft_memalloc(sizeof(t_walls))))
			yeet(al);
		set_coo(al, itop(-1, -1), 1, new->walls);
		set_coo(al, itop(-1, -1), 2, new->walls);
		new->next = al->sect;
		al->sect = new;
	}
	al->sect->nb_wal = 0;
}

void			add_sector(t_al *al, t_point coo)
{
	init_sect(al, al->sect);
	set_coo(al, coo, 1, al->sect->walls);
	set_coo(al, coo, 2, al->sect->walls);
}

void			add_wall(t_al *al, t_sector *sect, t_point coo)
{
	t_walls		*new;
	
	if (sect->walls->x1 == sect->walls->x2 && sect->walls->y1 == sect->walls->y2)
		return ;
	if (!(new = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	new->x1 = sect->walls->x2;
	new->y1 = sect->walls->y2;
	new->x2 = sect->walls->x2;
	new->y2 = sect->walls->y2;
	new->next = sect->walls;
	sect->walls = new;
	if (check_end_sector(sect->walls->next, coo.x - (coo.x % al->edit.zoom),
		coo.y - (coo.y % al->edit.zoom)) == 1)
		al->edit.stat = SELECT;
}
