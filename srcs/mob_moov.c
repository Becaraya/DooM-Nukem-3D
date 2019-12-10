/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_moov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:09:55 by hutricot          #+#    #+#             */
/*   Updated: 2019/12/10 16:25:13 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		is_cr(t_mob *e, t_walls t, double v, int s)
{
	(void)e;
	(void)t;
	(void)v;
	(void)s;
	/*
	double d;

	d = (s) ? d_wall(t, e->posx, e->posy + v) : d_wall(t, e->posx + v, e->posy);
	if (d < 0.5)
		return (0);*/
	return (1);
}

void	ft_nop(t_al *al,t_mob *e, double x, double y)
{
	int m[2];
	t_walls t;
	int		i;
	unsigned int s;

	i = 0;
	s = e->csec;
	m[0] = 1;
	m[1] = 1;
	while (i < (int)al->sec[e->csec].nb_wal)
	{
		t = al->sec[e->csec].walls[i];
		if (x > 0.0 && (t.x1 > e->posx || t.x2 > e->posx)
		&& ((t.y1 <= e->posy && e->posy <= t.y2) || (t.y1 >= e->posy && e->posy >= t.y2)))
			m[0] = is_cr(e, t ,x ,0);

		if (x < 0.00000 && (t.x1 < e->posx || t.x2 < e->posx)
		&& ((t.y1 <= e->posy && e->posy <= t.y2) || (t.y1 >= e->posy && e->posy >= t.y2)))
			m[0] = is_cr(e, t, x, 0);


		if (y > 0.0 && (t.y1 > e->posy || t.y2 > e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2) || (t.x1 >= e->posx && e->posx >= t.x2)))
			m[1] = is_cr(e, t, y, 1);

		if (y < 0.00000 && (t.y1 < e->posy || t.y2 < e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2) || (t.x1 >= e->posx && e->posx >= t.x2)))
			m[1] = is_cr(e, t, y, 1);
		if(e->csec != s){
			break;
		}
		i++;
	}
	(m[1] == 1) ? e->posy += y : 0;
	(m[0] == 1) ? e->posx += x : 0;
}