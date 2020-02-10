/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   won.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:13:43 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/06 10:50:30 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			inwin(unsigned x, unsigned y)
{
	return (x >= 0 && x < WIN_SIZEX && y >= 0 && y < WIN_SIZEY);
}

void		pront_uwon(t_al *al, double scale, double alpha)
{
	t_tex		yd;
	unsigned	x;
	unsigned	y;
	t_point		win;
	unsigned	tmp;

	yd = al->you_win;
	y = 0;
	win.x = WIN_SIZEX / 2 - (yd.size_x * scale) / 2;
	win.y = WIN_SIZEY / 2 - (yd.size_y * scale) / 2;
	while (y < yd.size_y * scale)
	{
		x = 0;
		while (x < yd.size_x * scale)
		{
			tmp = yd.pix[(unsigned)(y / scale) * yd.size_x + (unsigned)(x /
					scale)];
			if (inwin(x + win.x, y + win.y))
				tmp != 0xffff ? al->pix[(y + win.y) * WIN_SIZEX + x + win.x] =
				alphapix(tmp, alpha) : 0;
			x++;
		}
		y++;
	}
}

void		won(t_al *al)
{
	static int	stat = 0;
	double		scale;

	stat += al->dtime;
	stat == 1000000 ? stat = 1000001 : 0;
	scale = 20 - 18 * (stat / 3000000.0);
	pix_to_pix(al->pix_dead, al->pix, (10000000 - stat) / 10000000.0);
	if (stat < 3000000)
		pront_uwon(al, scale, stat / 3000000.0);
	else
		pront_uwon(al, 2, 1);
	refresh(al);
}
