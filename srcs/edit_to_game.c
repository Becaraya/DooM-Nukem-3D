/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_to_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 10:39:36 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/29 14:39:49 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

static void		edit_to_gamer(t_al *al)
{
	set_text(&al->text.t, "TEXT", get_rect(300, 330),
		add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	SDL_FreeSurface(al->surf_ed);
	SDL_DestroyWindow(al->win_ed);
	if (!al->edit.sect_end)
		convert_end(al);
	al->surf_ed = 0;
	al->win_ed = 0;
	load_pig(al);
	al->status = GAME;
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
		sector_to_game(al, cur, id);
		cur = cur->next;
		id++;
	}
	edit_to_gamer(al);
}
