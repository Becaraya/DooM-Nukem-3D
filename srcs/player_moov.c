/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/06 14:51:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	d_wall(t_walls w, double px, double py)
{
	double	a[2];
	double	b[2];
	double	x;
	double	y;

	if (w.x2 - w.x1 == 0)
		w.x2 += 0.0000001;
	if (w.y2 - w.y1 == 0)
		w.x2 += 0.0001;
	a[0] = (w.y2 - w.y1) / (w.x2 - w.x1);
	a[0] += 0.001;
	b[0] = w.y2 - (a[0] * w.x2);
	b[0] += 0.0001;
	a[1] = -1 / a[0];
	a[1] += 0.0001;
	b[1] = py - (a[1] * px);
	b[1] += 0.0001;
	x = ((b[0] / a[1]) - (b[1] / a[1])) / (a[1] / a[1] - (a[0] / a[1]));
	y = (a[0] * x) + b[0];
	return (sqrt((x - px) * (x - px) + (y - py) * (y - py)));
}

int		is_cross_x(t_player *e, t_walls t, double v, t_al *al)
{
	double d;

	d = d_wall(t, e->posx + v, e->posy);
	if (t.is_cross && d < GRO)
	{
		if (e->posz + 0.5 < al->sec[t.sec_lnk].fl_hei ||
		e->posz + e->size > al->sec[t.sec_lnk].ce_hei ||
		al->sec[t.sec_lnk].ce_hei - al->sec[t.sec_lnk].fl_hei < e->size)
			return (0);
		else
			return (1);
	}
	if (d < GRO)
		return (0);
	return (1);
}

int		is_cross_y(t_player *e, t_walls t, double v, t_al *al)
{
	double d;

	d = d_wall(t, e->posx, e->posy + v);
	if (t.is_cross && d < GRO)
	{
		if (e->posz + 0.5 < al->sec[t.sec_lnk].fl_hei ||
		e->posz + e->size > al->sec[t.sec_lnk].ce_hei ||
		al->sec[t.sec_lnk].ce_hei - al->sec[t.sec_lnk].fl_hei < e->size)
			return (0);
		else
			return (1);
	}
	if (d < GRO)
		return (0);
	return (1);
}

void	wall_ok(t_al *al, t_walls t, t_doint p, t_point *m)
{
	t_player j;

	j = al->play;
	if (p.x > 0.0 && (t.x1 >= j.posx + p.x || t.x2 >= j.posx + p.x)
		&& ((t.y1 <= j.posy && j.posy <= t.y2)
			|| (t.y1 >= j.posy && j.posy >= t.y2)))
		(!(is_cross_x(&al->play, t, p.x, al))) ? m->x = 0 : 1;
	if (p.x < 0.0 && (t.x1 <= j.posx + p.x || t.x2 <= j.posx + p.x)
		&& ((t.y1 <= j.posy && j.posy <= t.y2)
				|| (t.y1 >= j.posy && j.posy >= t.y2)))
		(!(is_cross_x(&al->play, t, p.x, al))) ? m->x = 0 : 1;
	if (p.y > 0.0 && (t.y1 >= j.posy + p.y || t.y2 >= j.posy + p.y)
		&& ((t.x1 <= j.posx + p.x && j.posx + p.x <= t.x2)
				|| (t.x1 >= j.posx + p.x && j.posx + p.x >= t.x2)))
		(!(is_cross_y(&al->play, t, p.y, al))) ? m->y = 0 : 1;
	if (p.y < 0.0 && (t.y1 <= j.posy + p.y || t.y2 <= j.posy + p.y)
		&& ((t.x1 <= j.posx + p.x && j.posx + p.x <= t.x2)
				|| (t.x1 >= j.posx + p.x && j.posx + p.x >= t.x2)))
		(!(is_cross_y(&al->play, t, p.y, al))) ? m->y = 0 : 1;
}

void	ft_nop_player(t_al *al, int i, double x, double y)
{
	t_point m;
	t_doint p;
	t_walls w;

	m.x = 1;
	m.y = 1;
	p.x = x;
	p.y = y;
	while (i < (int)al->sec[al->play.csec].nb_wal)
	{
		w = al->sec[al->play.csec].walls[i];
		wall_ok(al, al->sec[al->play.csec].walls[i], p, &m);
		i++;
	}
	(m.y == 1) ? al->play.posy += y : 0;
	(m.x == 1) ? al->play.posx += x : 0;
	al->play.csec = is_in_sector(al, al->play.posx, al->play.posy);
	if (!al->play.csec || (al->end && al->play.csec == al->end))
		al->play.won = 1;
	al->play.on_ground = 0;
}

/*
**if ((al->play.posx + x - w.x1) * (al->play.posx + x - w.x1) +
**(al->play.posy - w.y1) * (al->play.posy - w.y1) < 1 &&
**(al->play.posz + 0.5 < al->sec[w.sec_lnk].fl_hei ||
**	al->play.posz + al->play.size > al->sec[w.sec_lnk].ce_hei ||
**	al->sec[w.sec_lnk].ce_hei - al->sec[w.sec_lnk].fl_hei < al->play.size))
**		m.x = 0;
**	if ((al->play.posx + x- w.x1) * (al->play.posx+ x - w.x1) +
**(al->play.posy + y - w.y1) * (al->play.posy + y - w.y1) < 1 &&
**(al->play.posz + 0.5 < al->sec[w.sec_lnk].fl_hei ||
**	al->play.posz + al->play.size > al->sec[w.sec_lnk].ce_hei ||
**	al->sec[w.sec_lnk].ce_hei - al->sec[w.sec_lnk].fl_hei < al->play.size))
**		m.y = 0;
** 07/novembre
** il y avais un numeros de telephone ici 14.12 10.88
*/
