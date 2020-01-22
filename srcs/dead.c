/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:13:43 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/21 15:54:41 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

unsigned	alphapix(unsigned pix, double alpha)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = pix >> 16;
	g = pix >> 8;
	b = pix;
	r *= alpha;
	g *= alpha;
	b *= alpha;
	return ((r << 16) + (g << 8) + b);
}

void		pix_to_pix(unsigned *src, unsigned *dst, double alpha)
{
	unsigned		i;

	alpha < 0 ? alpha = 0 : 0;
	alpha > 1 ? alpha = 1 : 0;
	i = 0;
	while (i < WIN_SIZEX * WIN_SIZEY)
	{
		dst[i] = alphapix(src[i], alpha);
		i++;
	}
}

void		pront_urded(t_al *al, double scale, double alpha)
{
	t_tex		yd;
	unsigned	x;
	unsigned	y;
	unsigned	winx;
	unsigned	winy;
	unsigned	tmp;

	yd = al->you_died;
	y = 0;
	winx = WIN_SIZEX / 2 - yd.size_x / 2;
	winy = WIN_SIZEY / 2 - yd.size_y / 2;
	while (y < yd.size_y)
	{
		x = 0;
		while (x < yd.size_x)
		{
			tmp = yd.pix[y * yd.size_x + x];
			tmp != 0xffff ? al->pix[(y + winy) * WIN_SIZEX + x + winx] =
			alphapix(tmp, alpha) : 0;
			x++;
		}
		y++;
	}
}

void	dead(t_al *al)
{
	static int	stat = 0;

	stat += al->dtime;
	stat == 1000000 ? stat = 1000001 : 0;
	pix_to_pix(al->pix_dead, al->pix, (2000000 - stat) / 2000000.0);
	if (stat < 1000000)
		pront_urded(al, 1, stat / 1000000.0);
	else if (stat < 3000000)
		pront_urded(al, 1, 1);
	else if (stat < 4000000)
		pront_urded(al, 1, (4000000 - stat) / 1000000.0);
	refresh(al);
}
