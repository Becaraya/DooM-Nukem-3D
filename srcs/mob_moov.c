/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_moov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:09:55 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/28 12:42:50 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static double	d_wall(t_walls w, double px, double py)
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

static int		is_cross_x(t_mob *e, t_walls t, double v, t_al *al)
{
	double	d;

	d = d_wall(t, e->posx + v, e->posy);
	if ((d < 0.5) && t.is_cross)
	{
		if (e->posz + 0.5 < al->sec[t.sec_lnk].fl_hei ||
		e->posz + e->size > al->sec[t.sec_lnk].ce_hei ||
		al->sec[t.sec_lnk].ce_hei - al->sec[t.sec_lnk].fl_hei < e->size)
			return (0);
		else
			return (1);
	}
	if (d < 0.5)
		return (0);
	return (1);
}

static int		is_cross_y(t_mob *e, t_walls t, double v, t_al *al)
{
	double d;

	d = d_wall(t, e->posx, e->posy + v);
	if ((d < 0.5) && t.is_cross)
	{
		if (e->posz + 0.5 < al->sec[t.sec_lnk].fl_hei ||
		e->posz + e->size > al->sec[t.sec_lnk].ce_hei ||
		al->sec[t.sec_lnk].ce_hei - al->sec[t.sec_lnk].fl_hei < e->size)
			return (0);
		else
			return (1);
	}
	if (d < 0.5)
		return (0);
	return (1);
}

static void		wall_ok(t_al *al, t_mob *e, t_walls t, t_oint *o)
{
	if (o->d.x > 0.0 && (t.x1 >= e->posx || t.x2 >= e->posx)
		&& ((t.y1 <= e->posy && e->posy <= t.y2)
			|| (t.y1 >= e->posy && e->posy >= t.y2)))
		(!(is_cross_x(e, t, o->d.x, al))) ? o->p.x = 0 : 1;
	if (o->d.x < 0.0 && (t.x1 <= e->posx || t.x2 <= e->posx)
		&& ((t.y1 <= e->posy && e->posy <= t.y2)
				|| (t.y1 >= e->posy && e->posy >= t.y2)))
		(!(is_cross_x(e, t, o->d.x, al))) ? o->p.x = 0 : 1;
	if (o->d.y > 0.0 && (t.y1 >= e->posy || t.y2 >= e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2)
				|| (t.x1 >= e->posx && e->posx >= t.x2)))
		(!(is_cross_y(e, t, o->d.y, al))) ? o->p.y = 0 : 1;
	if (o->d.y < 0.0 && (t.y1 <= e->posy || t.y2 <= e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2)
				|| (t.x1 >= e->posx && e->posx >= t.x2)))
		(!(is_cross_y(e, t, o->d.y, al))) ? o->p.y = 0 : 1;
}

void			ft_nop(t_al *al, t_mob *e, double x, double y)
{
	t_oint	o;
	int		i;

	acceleration_entities(al, e);
	i = 0;
	o.p.x = 1;
	o.p.y = 1;
	o.d.x = x;
	o.d.y = y;
	while (i < (int)al->sec[e->csec].nb_wal)
	{
		wall_ok(al, e, al->sec[e->csec].walls[i], &o);
		i++;
	}
	(o.p.y == 1 && e->vely != 0 && e->alive) ? e->posy += y : 0;
	(o.p.x == 1 && e->velx != 0 && e->alive) ? e->posx += x : 0;
	mob_on_z(al, e);
	e->csec = is_in_sector(al, e->posx, e->posy);
}
