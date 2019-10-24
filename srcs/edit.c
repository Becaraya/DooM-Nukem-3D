/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/24 11:12:34 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"


// static void		icon_edit(t_al *al)
// {
// 	for (int i = 0; i < 699; i++){
// 		for (int j = 0; j < 604; j++){
// 			al->pix[699 * j + i] = al->txt.ic.chest[j * 699 + i];
// 		}
// 	}
// }

// Uint32 couleur(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
// {
//    return r << 24 | g << 16 | b << 8 | a;
// }

static void		set_edit(t_al *al)
{
	int			x;
	int 		y;
	Uint32		*pix;
	/* si tu veut init une grosse zone a null utilise bzero plutot  que des for
	ou while. Et fait des typedef sur la win_size plutot que hardcode les val */
	x = 0;
	y = 0;

	pix = al->sdlsurf->pixels;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	// SDL_LockSurface(al->sdlsurf);
	while (x < WIN_SIZEX)
	{
		while (y < WIN_SIZEY)
		{
			if (((x % (al->edit.zoom)) == 0) && (y % (al->edit.zoom) == 0) && y > 0 && x > 0)
				pix[x + (y * WIN_SIZEX)] = WHITE;
			y++;
		}
		y = 0;
		x++;
	}
	// SDL_UnlockSurface(al->sdlsurf);
}

void			ft_put_line(t_point a, t_point b, t_al *al, Uint32 *pix)
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
		pix[cur.x + cur.y * WIN_SIZEX] = WHITE;
		// printf("x = %d y = %d\n", cur.x, cur.y);
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

void		put_rectangle(t_point a, t_point b, t_al *al)
{
	t_point		c;
	t_point		d;
	Uint32 *pix;

	pix = al->sdlsurf->pixels;
	c.x = a.x;
	c.y = b.y;
	d.x = b.x;
	d.y = a.y;
	ft_put_line(a, d, al, pix);
	ft_put_line(a, c, al, pix);
	ft_put_line(c, b, al, pix);
	ft_put_line(d, b, al, pix);
}

void		draw_wall(t_al *al, t_wall *wall)
{
	t_point		a;
	t_point		b;
	Uint32 *pix;

	pix = al->sdlsurf->pixels;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	if (wall->type == RECT)
		(wall->x2 != -1) ? put_rectangle(a, b, al) : 0;
	else
		(wall->x2 != -1) ? ft_put_line(a, b, al, pix) : 0;
	if (wall->next)
		draw_wall(al, wall->next);
}

void	editor(t_al *al)
{
	set_edit(al);
	if (al->k.space == 1)
	{
		if (al->edit.stat == RECTANGLE_DRAW
			|| al->edit.stat == RECTANGLE_SELECT)
				al->edit.stat = RECTANGLE_SELECT;
		else
			al->edit.stat = FIRST_CLICK;
		al->wall->x1 = -1;
		al->wall->y1 = -1;
		al->wall->x2 = -1;
		al->wall->y2 = -1;
	}
	draw_wall(al, al->wall);
	// icon_edit(al);
	refresh(al);
}
