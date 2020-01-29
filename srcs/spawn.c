/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:04:08 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 15:41:05 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	set_spawn(t_al *al, SDL_MouseButtonEvent spw)
{
	t_point	tmp;

	tmp.x = spw.x - (spw.x % al->edit.zoom);
	tmp.y = spw.y - (spw.y % al->edit.zoom);
	al->play.posx = (tmp.x - (WIN_SIZEX / 2)) / 10;
	al->play.posy = (tmp.y - (WIN_SIZEY / 2)) / -10;
}

void	convert_end(t_al *al)
{
	t_point tmp;

	tmp.x = (al->end_sect.x - (WIN_SIZEX / 2)) / 10;
	tmp.y = (al->end_sect.y - (WIN_SIZEY / 2)) / -10;
	al->edit.sect_end = is_in_sector(al, (int)tmp.x, (int)tmp.y);
	if (!al->edit.sect_end)
		al->edit.sect_end = -1;
}

void	set_end(t_al *al, SDL_MouseButtonEvent bev)
{
	al->end_sect.x = bev.x - (bev.x % al->edit.zoom);
	al->end_sect.y = bev.y - (bev.y % al->edit.zoom);
	al->edit.spawnz = 0;
	al->edit.sect_end = 0;
}
