/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/06 14:42:15 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
**a therme l idée est de pouvoir appeller la fonction.
*/

double		d_wall(t_walls w, t_player e)
{
	double	a[2];
	double	b[2];
	double	x;
	double	y;

	if (w.x2 - w.x1 == 0)
		w.x2 += 0.00001;
	if (w.y2 - w.y1 == 0)
		w.x2 += 0.00001;
	a[0] = (w.y2 - w.y1) / (w.x2 - w.x1);
	a[0] += 0.001;
	b[0] = w.y2 - (a[0] * w.x2);
	b[0] += 0.0001;
	a[1] = -1 / a[0];
	a[1] += 0.0001;
	b[1] = e.posy - (a[1] * e.posx);
	b[1] += 0.0001;
	x = ((b[0] / a[1]) - (b[1] / a[1])) / (a[1] / a[1] - (a[0] / a[1]));
	y = (a[0] * x) + b[0];
	printf("%f,\n",sqrt((x - e.posx) * (x - e.posx) + (y - e.posy) * (y - e.posy)));
	return (sqrt((x - e.posx) * (x - e.posx) + (y - e.posy) * (y - e.posy)));
}

/*
**ft_nop empeche l'entité de passer au travers d un mur il faudrais lui trouver un nom plus paralans
**0.5 correspond a la moitier de l aipaisseur du joueur (je supose)
**il serais interesant de le fair varier pour en juger
*/


void	ft_nop_player(t_al *al, int i, double x, double y)
{
	double m[2];
	//double x[2];

	m[0] = 1;
	m[1] = 1;
	t_walls t;

	while (i < (int)al->sec[al->play.csec].nb_wal)
	{
		t = al->sec[al->play.csec].walls[i];
		if (x > 0.0 && (t.x1 > al->play.posx || t.x2 > al->play.posx) 
		&& ((t.y1 < al->play.posy && al->play.posy < t.y2) || (t.y1 > al->play.posy && al->play.posy > t.y2)))
			(d_wall(t, al->play) < 0.5) ? m[0] = 0 : 1;	
		if (x <= 0.0 && (t.x1 < al->play.posx || t.x2 < al->play.posx)
		&& ((t.y1 < al->play.posy && al->play.posy < t.y2) || (t.y1 > al->play.posy && al->play.posy > t.y2)))
			(d_wall(t, al->play) < 0.5) ? m[0] = 0 : 1;	
		if (y > 0.0 && (t.y1 > al->play.posy || t.y2 > al->play.posy)
		&& ((t.x1 < al->play.posx && al->play.posx < t.x2) || (t.x1 > al->play.posx && al->play.posx > t.x2)))
			(d_wall(t, al->play) < 0.5) ? m[1] = 0 : 1;	
		if (y <= 0.0 && (t.y1 < al->play.posy || t.y2 < al->play.posy)
		&& ((t.x1 < al->play.posx && al->play.posx < t.x2) || (t.x1 > al->play.posx && al->play.posx > t.x2)))
			(d_wall(t, al->play) < 0.5) ? m[1] = 0 : 1;	
		i++;
	}
	(m[1] == 1) ? al->play.posy += y : 0;
	(m[0] == 1) ? al->play.posx += x : 0; 
}
/*
void	ft_nop(t_al *al, int i, double x, double y)
{
	int m[2];

	m[0] = 0;
	m[1] = 0;
	t_walls t;
	while (i < (int)al->sec[al->ent.csec].nb_wal)
	{
		t = al->sec[al->ent.csec].walls[i];
		if (x > 0.0 && (t.x1 > al->ent.posx || t.x2 > al->ent.posx)
			&& ((t.y1 < al->ent.posy && al->ent.posy < t.y2) || (t.y1 > al->ent.posy && al->ent.posy > t.y2)))
			(d_wall(t, al->ent) > 0.5) ? m[0] = 1 : 0;
		if (x < 0.0 && (t.x1 < al->ent.posx || t.x2 < al->ent.posx)
			&& ((t.y1 < al->ent.posy && al->ent.posy < t.y2) || (t.y1 > al->ent.posy && al->ent.posy > t.y2)))
			(d_wall(t, al->ent) > 0.5) ? m[0] = 1 : 0;
		if (y > 0.0 && (t.y1 > al->ent.posy || t.y2 > al->ent.posy)
			&& ((t.x1 < al->ent.posx && al->ent.posx < t.x2) || (t.x1 > al->ent.posx && al->ent.posx > t.x2)))
			(d_wall(t, al->ent) > 0.5) ? m[1] = 1 : 0;
		if (y < 0.0 && (t.y1 < al->ent.posy || t.y2 < al->ent.posy)
			&& ((t.x1 < al->ent.posx && al->ent.posx < t.x2) || (t.x1 > al->ent.posx && al->ent.posx > t.x2)))
			(d_wall(t, al->ent) > 0.5) ? m[1] = 1 : 0;
		i++;
	}
	(m[1]) ? al->ent.posy += y : 0;
	(m[0]) ? al->ent.posx += x : 0; 
}
*/
void    mv_entity(t_al *al)
{
//	ft_nop(al,0,0.05, 0.2);
}
