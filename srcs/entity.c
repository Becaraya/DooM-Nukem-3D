/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:13:02 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/29 15:44:01 by pitriche         ###   ########.fr       */
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

static int	is_left(t_doint p0, t_doint p1, t_doint p2)
{
	int		value;	value = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
	if (value == 0)
		return (0);
	else if (value > 0)
		return (1);
	else
		return (2);
}

int			intersects_count(t_doint v1, t_doint v2, t_doint p1, t_doint p2)
{
	int		tab[4];	tab[0] = is_left(v1, v2, p1);
	tab[1] = is_left(v1, v2, p2);
	tab[2] = is_left(p1, p2, v1);
	tab[3] = is_left(p1, p2, v2);
	if (tab[0] != tab[1] && tab[2] != tab[3])
		return (1);
	return (0);
}

static int	inters(t_sector sec, t_doint point, t_doint extreme)
{
	int		intersections;
	t_doint a;
	t_doint b;
	unsigned i;

	i = 0;
	intersections = 0;
	//printf("its ok bro\n");
	while (i < sec.nb_wal)
	{
	//	printf("i:%d\n", i);
		a.x = sec.walls[i].x1;
		a.y = sec.walls[i].y1;
		b.x = sec.walls[i].x2;
		b.y = sec.walls[i].y2;
		if (i + 1 == sec.nb_wal)
		{
			if (intersects_count(a, b, point, extreme))
				++intersections;
		}
		else if (intersects_count(a, b, point, extreme))
			++intersections;
		i++;
	}
	return (intersections);
}

#define MAX_X 10000 //c est temporaire j ai la flemme pour le moment 
int            is_in_sector(t_doint point, unsigned i, t_al *al)
{
    int            se;

    t_doint    extreme; // mur en x le plus loin et y actuel
		//printf("it's ok bro");
    while (i - 1 < al->nb_sec)
    {
		//printf("sec: %d\n", i);
        extreme.x = MAX_X;
        extreme.y = point.y;
        se = inters(al->sec[i], point, extreme );
	//	printf("inter %d\n", se % 2);
        if (se % 2 == 1)
            return (i);
        i++;
    }
	printf("YASUNE COUILLLLLLLLLLLLLLLL\n");
    return (1);
}

/*
**ft_nop empeche l'entité de passer au travers d un mur il faudrais lui trouver un nom plus paralans
**0.5 correspond a la moitier de l aipaisseur du joueur (je supose)
**il serais interesant de le fair varier pour en juger
*/

//version fonctionelle du ft_nop-PLAYER
// void	ft_nop_p`layer(t_al *al, int i, double x, double y)
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

int		is_cross(t_player *e, t_walls t, double v, int s, t_al *al)
{
	double d;
	t_doint j;
	 
	j.x = e->posx;
	j.y = e->posy;
	printf("sector : %d\n", is_in_sector(j, 1, al));
	d = (s) ? d_wall(t, e->posx, e->posy + v) : d_wall(t, e->posx + v, e->posy);
	if (t.is_cross)
		return(1);
	if(s)
	{
		j.y += v;
		e->csec =  is_in_sector(j, 1, al);
	}
	else
	{
		j.x += v;
		e->csec =  is_in_sector(j, 1, al);
	}
	if (d < 0.5)
		return (0);
	return (1);
}
/*
int            is_in_sector(t_editor *edit, t_vertex point)
{
    int            intersects;
    t_sector    *sect;
    t_vertex    *vertex;
    t_vertex    extreme;

    sect = edit->sector;
    while (sect)
    {
        extreme.x = WHITE;
        extreme.y = point.y;
        vertex = sect->vertex;
        intersects = inters(vertex, point, extreme);
        if (intersects % 2 == 1)
            return (sect->sector_number);
        sect = sect->next;
    }
    return (-1);
}*/

void	ft_nop_player(t_al *al, int i, double x, double y)
{
	double m[2];
	t_walls t;

	m[0] = 1;  
	m[1] = 1;
	while (i < (int)al->sec[al->play.csec].nb_wal)
	{
		t = al->sec[al->play.csec].walls[i];
		if (x > 0.0 && (t.x1 >= PPX || t.x2 >= PPX) 
		&& ((t.y1 <= PPY && PPY <= t.y2) || (t.y1 >= PPY && PPY >= t.y2)))
			m[0] = is_cross(&al->play, t, x, 0, al);
		if (x <= 0.0 && (t.x1 <= PPX || t.x2 <= PPX)
		&& ((t.y1 <= PPY && PPY <= t.y2) || (t.y1 >= PPY && PPY >= t.y2)))
			m[0] = is_cross(&al->play, t, x, 0, al);	
		if (y > 0.0 && (t.y1 >= PPY || t.y2 >= PPY)
		&& ((t.x1 <= PPX && PPX <= t.x2) || (t.x1 >= PPX && PPX >= t.x2)))
			m[1] = is_cross(&al->play, t, y, 1, al);	
		if (y <= 0.0 && (t.y1 <= PPY || t.y2 <= PPY)
		&& ((t.x1 <= PPX && PPX <= t.x2) || (t.x1 >= PPX && PPX >= t.x2)))
			m[1] = is_cross(&al->play, t, y, 1, al);	
		i++;
	}
	(m[1] == 1) ? PPY += y : 0;
	(m[0] == 1) ? PPX += x : 0;
}

int		is_cross_x(t_mob *e, t_walls t, double v, int s)
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
			m[0] = is_cross_x(e, t ,x ,0);

		if (x < 0.00000 && (t.x1 < e->posx || t.x2 < e->posx)
		&& ((t.y1 <= e->posy && e->posy <= t.y2) || (t.y1 >= e->posy && e->posy >= t.y2)))
			m[0] = is_cross_x(e, t, x, 0);

		if (y > 0.0 && (t.y1 > e->posy || t.y2 > e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2) || (t.x1 >= e->posx && e->posx >= t.x2)))
			m[1] = is_cross_x(e, t, y, 1);

		if (y < 0.00000 && (t.y1 < e->posy || t.y2 < e->posy)
		&& ((t.x1 <= e->posx && e->posx <= t.x2) || (t.x1 >= e->posx && e->posx >= t.x2)))
			m[1] = is_cross_x(e, t, y, 1);
	//	printf("ex: %f , t.x1: %f, t.x2: %f\n", e->posx, );
		if(e->csec != s){
		printf("coucou\n");
		printf("%d\n",e->csec);
			break;
		}
		i++;
	}
	(m[1] == 1) ? e->posy += y : 0;
	(m[0] == 1) ? e->posx += x : 0;
}

/*
** 07/novembre
** 0145174039
*/