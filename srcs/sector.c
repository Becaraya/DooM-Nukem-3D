/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:36:27 by hutricot          #+#    #+#             */
/*   Updated: 2019/12/03 14:40:54 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static int	is_left(t_doint p0, t_doint p1, t_doint p2)
{
	int		value;
	
	value = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
	if (value == 0)
		return (0);
	else if (value > 0)
		return (1);
	else
		return (2);
}

int			intersects_count(t_doint v1, t_doint v2, t_doint p1, t_doint p2)
{
	int		tab[4];
	
	tab[0] = is_left(v1, v2, p1);
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

#define MAX_X 100 //c est temporaire j ai la flemme pour le moment il faudrais mettre une variable x max deffinicant le point x le plus eloigner
int            is_in_sector(t_al *al, double x, double y)
{
	unsigned	i;
    t_doint		extreme; // mur en x le plus loin et y actuel
	t_doint		point;

	point.x = x;
	point.y = y;
	i = 1;
	while (i - 1 < al->nb_sec)
    {
        extreme.x = MAX_X;
        extreme.y = point.y;
        if (inters(al->sec[i], point, extreme) % 2 == 1)
		{
            return (i);
		}
		i++;
    }
	printf("YASUNE COUILLLLLLLLLLLLLLLL\n");
    return (1);
}