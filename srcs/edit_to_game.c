/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_to_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 10:39:36 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 16:19:50 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

	sec = al->sec + id;
	sec->fl_hei = cur->fl_hei;
	sec->ce_hei = cur->ce_hei;
	sec->fl_tex = cur->fl_tex;
	sec->ce_tex = cur->ce_tex;
	sec->nb_wal = how_many_walls(cur);
	if (!(sec->walls = ft_memalloc(sec->nb_wal * sizeof(t_walls))))
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

void			edit_to_game(t_al *al)
{
	t_sector	*cur;
	unsigned	id;

	link_sectors(al);
	(!(cur = al->sect)) ? ft_putstr("Empty map\n") : 0;
	if (!cur)
		return ;
	al->nb_sec = how_many_sectors(al);
	al->tmp_sec = al->sec;
	if (!(al->sec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector))))
		exit(pr_err(MERROR_MESS));
	id = 0;
	while (cur && ++id)
	{
		sector_to_game(al, cur, id);
		cur = cur->next;
	}
	set_text(&al->text.t, "TEXT", get_rect(300, 330),
		add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	if (!al->edit.sect_end)
		convert_end(al);
	load_pig(al);
	!al->map_write_name ? al->map_write_name = "poi.hms" : 0;
	(hms_encoder(al, al->map_write_name)) ?
	finish_write(al, 1) : finish_write(al, 0);
}
