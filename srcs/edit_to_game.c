/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_to_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 10:39:36 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/27 14:47:22 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*static void	link_wall(t_sector *cur, t_walls *set, int id)
{
	t_walls	*wall;

	wall = cur->walls;
	while(wall)
	{
		if ((wall->x1 == set->x1 && wall->x2 == set->x2 && wall->y1 == set->y1
			&& wall->y2 == set->y2) ||
			(wall->x1 == set->x2 && wall->x2 == set->x1 &&wall->y1 == set->y2 && wall->y2 == set->y1))
		{
			set->sec_lnk = id + 1;
			//printf("link !  ");
			return;
		}
		wall = wall->next;
	}
}

static void	link_sector(t_sector *root, t_sector *cur, unsigned id)
{
	t_walls		*wall;
	unsigned	i;

	//printf("sec %d > fl_hei:%.2f\n", id, cur->fl_hei);
	i = 0;
	while (root)
	{
		wall = (i != id ? cur->walls : 0);
		//printf("check sec %d: [%s]\n", i, wall ? "TRUE" : "FALSE");
		while (wall)
		{
			//printf(" wall y1>%.0f ", wall->y1);
			link_wall(root, wall, i);
			wall = wall->next;
		}
		//i != id ? printf("\n") : 0;
		root = root->next;
		i++;
	}
	//	printf("\n");
}*/

static void		walls_to_game(t_walls *walls, t_sector *sec)
{
	unsigned	i;

	i = sec->nb_wal - 1;
	while (walls)
	{	
		sec->walls[i] = *walls;
		sec->walls[i].x1 = (sec->walls[i].x1 - WIN_SIZEX / 2) / 10.0;
		sec->walls[i].x2 = (sec->walls[i].x2 - WIN_SIZEX / 2) / 10.0;
		sec->walls[i].y1 = (sec->walls[i].y1 - WIN_SIZEY / 2) / -10.0;
		sec->walls[i].y2 = (sec->walls[i].y2 - WIN_SIZEY / 2) / -10.0;
	
		printf("NEW wall [%2.0f,%2.0f %2.0f,%2.0f] link [%c]\n",
		sec->walls[i].x1, sec->walls[i].y1, sec->walls[i].x2, sec->walls[i].y2,
		sec->walls[i].sec_lnk ? sec->walls[i].sec_lnk + '0' : 'X');
		
		walls = walls->next;
		i--;
	}
}

static unsigned	how_many_walls(t_sector *sec)
{
	t_walls		*cur;
	unsigned	i;

	cur = sec->walls;
	i = 0;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

static void		sector_to_game(t_al *al, t_sector *cur, unsigned id)
{
	t_sector	*sec;
	t_sector	*rotsec;
	t_walls		*wall;
	unsigned	i;

	sec = al->sec + id;
	rotsec = al->rotsec + id;
	sec->fl_hei = cur->fl_hei;
	sec->ce_hei = cur->ce_hei;
	sec->fl_tex = cur->fl_tex;
	sec->ce_tex = cur->ce_tex;
	sec->nb_wal = how_many_walls(cur);
	
	if (!(sec->walls = ft_memalloc(sec->nb_wal * sizeof(t_walls))) ||
		!(rotsec->walls = ft_memalloc(sec->nb_wal * sizeof(t_walls))))
		exit(pr_err(MERROR_MESS));
	walls_to_game(cur->walls, sec);
	

	printf("parse sec %.1f %.1f %hu %hu  [with %d walls]\n", sec->fl_hei,
	sec->ce_hei, sec->fl_tex, sec->ce_tex, cur->nb_wal);
}

static unsigned	how_many_sectors(t_al *al)
{
	t_sector	*cur;
	unsigned	i;

	cur = al->sect;
	i = 0;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

void			edit_to_game(t_al *al)
{
	t_sector	*cur;
	unsigned	id;

	link_sectors(al);
	(!(cur = al->sect)) ? ft_putstr("Empty map\n") : 0;
	if (!cur)
		return ;
	al->nb_sec = how_many_sectors(al);
	if (!(al->sec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector))) ||
		!(al->rotsec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector))))
		exit(pr_err(MERROR_MESS));
	id = 1;
	while (cur)
	{
		//printf("go sec %d\n", id);
		sector_to_game(al, cur, id);
		cur = cur->next;
		id++;
	}
	set_text(&al->text.t, "TEXT", get_rect(300, 330),
		add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	SDL_FreeSurface(al->surf_ed);
	SDL_DestroyWindow(al->win_ed);
	al->surf_ed = 0;
	al->win_ed = 0;
	al->status = GAME;
	printf("YEeYYEEeeTT %d sec\n", al->nb_sec);
}
