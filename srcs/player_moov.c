/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**a therme l idée est de pouvoir appeller la fonction.
*/

double		d_wall(t_walls w, double px, double py)
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

/*
**ft_nop empeche l'entité de passer au travers d un mur il faudrais lui trouver un nom plus paralans
**0.5 correspond a la moitier de l aipaisseur du joueur (je supose)
**il serais interesant de le fair varier pour en juger
*/

int		is_cross_x(t_player *e, t_walls t, double v, t_al *al)
{
	double d;

	d = d_wall(t, e->posx + v, e->posy);
	if (t.is_cross)
	{
		if ((d < 0.5)&& e->posz < al->sec[t.sec_lnk].fl_hei)
			return(0);
		else
			return(1);
	}
	if (d < 0.5)
		return (0);
	return (1);
}

int		is_cross_y(t_player *e, t_walls t, double v, int s)
{
	double d;
	t_doint j;
	 
	j.x = e->posx;
	j.y = e->posy;
	d = (s) ? d_wall(t, e->posx, e->posy + v) : d_wall(t, e->posx + v, e->posy);
	if (t.is_cross)
		return(1);
	if (d < 0.5)
		return (0);
	return (1);
}

void	ft_nop_player(t_al *al, int i, double x, double y)
{
	double m[2];
	t_walls t;

	m[0] = 1; 
	m[1] = 1;
	al->play.csec = is_in_sector(al, al->play.posx, al->play.posy);
	printf("\n\nsector : %d\n",al->play.csec);
	while (i < (int)al->sec[al->play.csec].nb_wal)
	{
		t = al->sec[al->play.csec].walls[i];
		if (x > 0.0 && (t.x1 >= PPX || t.x2 >= PPX) 
		&& ((t.y1 <= PPY && PPY <= t.y2) || (t.y1 >= PPY && PPY >= t.y2)))
			(!(is_cross_x(&al->play, t, x, al))) ? m[0] = 0 : 1;
		if (x <= 0.0 && (t.x1 <= PPX || t.x2 <= PPX)
		&& ((t.y1 <= PPY && PPY <= t.y2) || (t.y1 >= PPY && PPY >= t.y2)))
			(!(is_cross_x(&al->play, t, x, al))) ? m[0] = 0 : 1;
		if (y > 0.0 && (t.y1 >= PPY || t.y2 >= PPY)
		&& ((t.x1 <= PPX && PPX <= t.x2) || (t.x1 >= PPX && PPX >= t.x2)))
			m[1] = is_cross_y(&al->play, t, y, 1);	
		if (y <= 0.0 && (t.y1 <= PPY || t.y2 <= PPY)
		&& ((t.x1 <= PPX && PPX <= t.x2) || (t.x1 >= PPX && PPX >= t.x2)))
			m[1] = is_cross_y(&al->play, t, y, 1);	
		i++;
	}
	printf(" %f %f %f %f,", m[0], m[0], m[0], m[0]);
	(m[1] == 1) ? PPY += y : 0;
	(m[0] == 1) ? PPX += x : 0;
}


/*
** 07/novembre
** 0145174039
*/