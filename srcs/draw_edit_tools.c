/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_edit_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:12:32 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 11:31:31 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_wall(t_al *al, t_walls *wall, int clr)
{
	t_point		a;
	t_point		b;
	int			clr_tmp;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	clr_tmp = ((unsigned)clr == WHITE && wall->sec_lnk) ? LIGHT_GREY : clr;
	(wall->x1 != -1) ? ft_put_line(a, b, al->sdlsurf, clr_tmp) : 0;
	if (wall->next)
		draw_wall(al, wall->next, clr);
}

void		draw_wall_index(t_al *al, t_walls *wall, int index)
{
	t_point		a;
	t_point		b;
	int			clr;

	clr = wall->sec_lnk ? DARK_RED : RED;
	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	if (index == 0)
		clr = wall->sec_lnk ? DARK_YELLOW : YELLOW;
	(wall->x1 != -1) ? ft_put_line(a, b, al->sdlsurf, clr) : 0;
	if (wall->next)
		draw_wall_index(al, wall->next, index - 1);
}

void		draw_sect_index(t_al *al, t_sector *sect, unsigned int i_s)
{
	if (i_s == al->edit.index_sect)
		draw_wall_index(al, sect->walls, (int)al->edit.index_wall);
	else if (sect->next)
		draw_sect_index(al, sect->next, i_s - 1);
}

void		draw_sect(t_al *al, t_sector *sect)
{
	draw_wall(al, sect->walls, WHITE);
	if (sect->next)
		draw_sect(al, sect->next);
}
