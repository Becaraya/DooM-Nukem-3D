/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2019/10/29 15:51:37 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
**a therme l idée est de pouvoir appeller la fonction.
*/

double		d_wall(t_walls w, t_entity e)
{
	double	a[2];
	double	b[2];
	double	x;
	double	y;

	a[0] = (w.y2 - w.y1) / (w.x2 - w.x1);
	b[0] = w.y2 - (a[0] * w.x2);
	a[1] = -1 / a[0];
	b[1] = e.pl.posy - (a[1] * e.pl.posx);
	x = ((b[0] / a[1]) - (b[1] / a[1])) / (a[1] / a[1] - (a[0] / a[1]));
	y = (a[0] * x) + b[0];
	return (sqrt((x - e.pl.posx) * (x - e.pl.posx) + (y - e.pl.posy) * (y - e.pl.posy)));
}

/*
**ft_nop empeche l'entité de passer au travers d un mur il faudrais lui trouver un nom plus paralans
**0.5 correspond a la moitier de l aipaisseur du joueur (je supose)
**il serais interesant de le fair varier pour en juger
*/

void	ft_nop(t_al *al, int i, double x, double y)
{
	int m[2];

	m[0] = 0;
	m[1] = 0;
	t_walls t;
	while (i < (int)al->sec[2].nb_wal)
	{
		t = al->sec[1].walls[i];
		if (x > 0.0 && (t.x1 > al->ent.pl.posx || t.x2 > al->ent.pl.posx) && ((t.y1 < y && y < t.y2) || (t.y1 > y && y > t.y2)))
			(d_wall(t, al->ent) > 0.5) ? m[0] = 1 : 0;
		if (x <= 0.0 && (t.x1 < al->ent.pl.posx || t.x2 < al->ent.pl.posx) && ((t.y1 < y && y < t.y2) || (t.y1 > y && y > t.y2)))
			(d_wall(t, al->ent) > 0.5) ? m[0] = 1 : 0; 
		if (y > 0.0 && (t.y1 > al->ent.pl.posy || t.y2 > al->ent.pl.posy) && ((t.x1 < x && x < t.x2) || (t.x1 > x && x > t.x2)))
			(d_wall(t, al->ent) > 0.5) ? m [1]= 1 : 0;
		if (y < 0.0 && (t.y1 < al->ent.pl.posy || t.y2 < al->ent.pl.posy) && ((t.x1 < x && x < t.x2) || (t.x1 > x && x > t.x2)))
			(d_wall(t, al->ent) > 0.5) ? m[1] = 1 : 0;
		i++;
	}
	(m[1]) ? al->ent.pl.posy += y : 0;
	(m[0]) ? al->ent.pl.posx += x : 0; 
}

void    mv_entity(t_al *al)
{
	ft_nop(al,0,-0.02,0.02);
}
