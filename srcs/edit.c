/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/29 14:56:36 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		set_edit(t_al *al)
{
	int			x;
	int 		y;
	/* si tu veut init une grosse zone a null utilise bzero plutot  que des for
	ou while. Et fait des typedef sur la win_size plutot que hardcode les val */
	x = 0;
	y = 0;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	while (x < WIN_SIZEX)
	{
		while (y < WIN_SIZEY)
		{
			if (((x % (al->edit.zoom)) == 0) && (y % (al->edit.zoom) == 0) && y > 0 && x > 0)
				al->pix[x + (y * WIN_SIZEX)] = WHITE;
			y++;
		}
		y = 0;
		x++;
	}
}

void			ft_put_line(t_point a, t_point b, t_al *al)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			tab[2];

	delta.x = ft_abs(b.x - a.x);
	delta.y = ft_abs(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	tab[0] = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		al->pix[cur.x + cur.y * WIN_SIZEX] = WHITE;
		if ((tab[1] = tab[0] * 2) > -delta.y)
		{
			tab[0] -= delta.y;
			cur.x += sign.x;
		}
		if (tab[1] < delta.x)
		{
			tab[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void		draw_wall(t_al *al, t_walls *wall)
{
	t_point		a;
	t_point		b;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	(wall->x1 != -1) ? ft_put_line(a, b, al) : 0;
	if (wall->next)
		draw_wall(al, wall->next);
}

void		draw_sect(t_al *al, t_sector *sect)
{
	draw_wall(al, sect->walls);
	if (sect->next)
		draw_sect(al, sect->next);
}

void	editor(t_al *al)
{
	set_edit(al);
	if (al->sect)
		draw_sect(al, al->sect);
	refresh(al);
}
