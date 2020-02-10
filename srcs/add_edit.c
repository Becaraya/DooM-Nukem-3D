/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:08:39 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/06 14:44:40 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			set_coo(t_al *al, t_point bev, int who, t_walls *wall)
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

void			init_sec(t_al *al)
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

void			init_sect(t_al *al, t_sector *sect)
{
	t_sector	*new;

	new = NULL;
	if (!sect)
	{
		init_sec(al);
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
	al->sect->nb_wal = 1;
}

/*
** yeah that's ugly. and so are you
*/

void			correct_all_shit(t_sector *sect)
{
	t_walls	*wall;
	double	tmpx1;
	double	tmpy1;

	sect->ce_hei = 2.5;
	sect->fl_tex = 2;
	sect->ce_tex = 3;
	wall = sect->walls;
	while (wall)
	{
		tmpx1 = wall->x1;
		tmpy1 = wall->y1;
		wall->x1 = wall->x2;
		wall->y1 = wall->y2;
		wall->x2 = tmpx1;
		wall->y2 = tmpy1;
		if (!wall->sec_lnk && !wall->wall_tex)
			wall->wall_tex = 1;
		wall = wall->next;
	}
}

void			add_wall(t_al *al, t_sector *sect, t_point coo)
{
	t_walls		*new;

	if (sect->walls->x1 == sect->walls->x2 &&
		sect->walls->y1 == sect->walls->y2)
		return ;
	if (sect->walls->next &&
		check_end_sector(sect->walls->next, coo.x - (coo.x % al->edit.zoom),
		coo.y - (coo.y % al->edit.zoom)) == 1)
	{
		al->edit.stat = SELECT;
		al->edit.index_sect++;
		correct_all_shit(al->sect);
		return ;
	}
	if (!(new = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	sect->nb_wal++;
	new->x1 = sect->walls->x2;
	new->y1 = sect->walls->y2;
	new->x2 = sect->walls->x2;
	new->y2 = sect->walls->y2;
	new->next = sect->walls;
	sect->walls = new;
}
