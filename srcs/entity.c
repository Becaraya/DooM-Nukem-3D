/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/19 13:12:13 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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

//version fonctionelle du ft_nop-PLAYER
// void	ft_nop_player(t_al *al, int i, double x, double y)
// {
// 	double m[2];
// 	t_walls t;

// 	m[0] = 1;  
// 	m[1] = 1;
// 	while (i < (int)al->sec[al->play.csec].nb_wal)
// 	{
// 		t = al->sec[al->play.csec].walls[i];
// 		if (x > 0.0 && (t.x1 > PPX || t.x2 > PPX) 
// 		&& ((t.y1 < PPY && PPY < t.y2) || (t.y1 > PPY && PPY > t.y2)))
// 			(d_wall(t, PPX + x, PPY) < 0.5) ? m[0] = 0 : 1;	
// 		if (x <= 0.0 && (t.x1 < PPX || t.x2 < PPX)
// 		&& ((t.y1 < PPY && PPY < t.y2) || (t.y1 > PPY && PPY > t.y2)))
// 			(d_wall(t, PPX + x, PPY) < 0.5) ? m[0] = 0 : 1;
// 		if (y > 0.0 && (t.y1 > PPY || t.y2 > PPY)
// 		&& ((t.x1 < PPX && PPX < t.x2) || (t.x1 > PPX && PPX > t.x2)))
// 			(d_wall(t, PPX, PPY + y) < 0.5) ? m[1] = 0 : 1;
// 		if (y <= 0.0 && (t.y1 < PPY || t.y2 < PPY)
// 		&& ((t.x1 < PPX && PPX < t.x2) || (t.x1 > PPX && PPX > t.x2)))
// 			(d_wall(t, PPX, PPY + y) < 0.5) ? m[1] = 0 : 1;
// 		i++;
// 	}
// 	(m[1] == 1) ? PPY += y : 0;
// 	(m[0] == 1) ? PPX += x : 0; 
// }


void	ft_nop_player(t_al *al, int i, double x, double y)
{
	double m[2];
	t_walls t;

	m[0] = 1;  
	m[1] = 1;
	while (i < (int)al->sec[al->play.csec].nb_wal)
	{
		t = al->sec[al->play.csec].walls[i];
		if (x > 0.0 && (t.x1 > PPX || t.x2 > PPX) 
		&& ((t.y1 < PPY && PPY < t.y2) || (t.y1 > PPY && PPY > t.y2)))
			(d_wall(t, PPX + x, PPY) < 0.5) ? m[0] = 0 : 1;	
		if (x <= 0.0 && (t.x1 < PPX || t.x2 < PPX)
		&& ((t.y1 < PPY && PPY < t.y2) || (t.y1 > PPY && PPY > t.y2)))
			(d_wall(t, PPX + x, PPY) < 0.5) ? m[0] = 0 : 1;
		if (y > 0.0 && (t.y1 > PPY || t.y2 > PPY)
		&& ((t.x1 < PPX && PPX < t.x2) || (t.x1 > PPX && PPX > t.x2)))
			(d_wall(t, PPX, PPY + y) < 0.5) ? m[1] = 0 : 1;
		if (y <= 0.0 && (t.y1 < PPY || t.y2 < PPY)
		&& ((t.x1 < PPX && PPX < t.x2) || (t.x1 > PPX && PPX > t.x2)))
			if (d_wall(t, PPX, PPY + y) < 0.5)
			 m[1] = (t.is_cross) ? printf("j'ai un mur traversable") : 0;
		i++;
	}
	(m[1] == 1) ? PPY += y : 0;
	(m[0] == 1) ? PPX += x : 0; 
}

int		is_cross_x(t_entity *e, t_walls t, double v, int s)
{
	double d;

	d = (s) ? d_wall(t, e->px, e->py + v) : d_wall(t, e->px + v, e->py);
	if (d < 0.5)
		return (0);
	return (1);
}

void	ft_nop(t_al *al,t_entity *e, double x, double y)
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
		if (x > 0.0 && (t.x1 > e->px || t.x2 > e->px)
		&& ((t.y1 <= e->py && e->py <= t.y2) || (t.y1 >= e->py && e->py >= t.y2)))
			m[0] = is_cross_x(e, t ,x ,0);

		if (x < 0.00000 && (t.x1 < e->px || t.x2 < e->px)
		&& ((t.y1 <= e->py && e->py <= t.y2) || (t.y1 >= e->py && e->py >= t.y2)))
			m[0] = is_cross_x(e, t, x, 0);

		if (y > 0.0 && (t.y1 > e->py || t.y2 > e->py)
		&& ((t.x1 <= e->px && e->px <= t.x2) || (t.x1 >= e->px && e->px >= t.x2)))
			m[1] = is_cross_x(e, t, y, 1);

		if (y < 0.00000 && (t.y1 < e->py || t.y2 < e->py)
		&& ((t.x1 <= e->px && e->px <= t.x2) || (t.x1 >= e->px && e->px >= t.x2)))
			m[1] = is_cross_x(e, t, y, 1);
	//	printf("ex: %f , t.x1: %f, t.x2: %f\n", e->px, );
		if(e->csec != s){
		printf("coucou\n");
		printf("%d\n",e->csec);
			break;
		}
		i++;
	}
	(m[1] == 1) ? e->py += y : 0;
	(m[0] == 1) ? e->px += x : 0; 
}

// 07/novembre
// 0145174039
