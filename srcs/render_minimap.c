/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 00:23:02 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/29 15:49:54 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		map_draw(t_al *al, t_point a, t_point b)
{
	b.y = a.y + 5;
	b.x = a.x + 5;
	while (++a.y < b.y)
	{
		while (++a.x < b.x)
			al->pix[(int)(a.x + (a.y * WIN_SIZEX))] = 0x52fc03;
	}
	a.x = al->play.posx * 10 + (WIN_SIZEX + WIN_SIZEX / 2);
	a.y = -al->play.posy * 10 + (WIN_SIZEY - WIN_SIZEY / 2);
	b.x = a.x + al->sin[al->play.dir] * 10;
	b.y = a.y - al->cos[al->play.dir] * 10;
	ft_put_line(a, b, al->sdlsurf, WHITE);
	al->pix[(int)(a.x + (a.y * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + 1 + (a.y * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + ((a.y + 1) * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + 1 + ((a.y + 1) * WIN_SIZEX))] = 0xff00ff;
}

void			draw_map(t_al *al)
{
	t_point			a;
	t_point			b;
	unsigned int	nb_wal;
	unsigned int	nb_sec;

	nb_sec = 1;
	while (nb_sec <= al->nb_sec)
	{
		nb_wal = 0;
		while (nb_wal < al->sec[nb_sec].nb_wal)
		{
			a.x = al->sec[nb_sec].walls[nb_wal].x1 * 10 +
				(WIN_SIZEX + WIN_SIZEX / 2);
			a.y = -al->sec[nb_sec].walls[nb_wal].y1 * 10 +
				(WIN_SIZEY - WIN_SIZEY / 2);
			b.x = al->sec[nb_sec].walls[nb_wal].x2 * 10 +
				(WIN_SIZEX + WIN_SIZEX / 2);
			b.y = -al->sec[nb_sec].walls[nb_wal].y2 * 10 +
				(WIN_SIZEY - WIN_SIZEY / 2);
			ft_put_line(a, b, al->sdlsurf, 0xBF55EC);
			nb_wal++;
		}
		nb_sec++;
	}
	map_draw(al, a, b);
}
