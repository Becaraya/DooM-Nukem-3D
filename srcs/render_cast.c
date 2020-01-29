/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:03:56 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 15:47:10 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		rot_sec(t_al *al, unsigned int secid, t_angle angle)
{
	unsigned	i;
	t_sector	*rotsec;
	t_walls		*w;
	t_player	*play;

	rotsec = al->rotsec + secid;
	rotsec->nb_wal = al->sec[secid].nb_wal;
	play = &al->play;
	i = 0;
	while (i < rotsec->nb_wal)
	{
		w = al->sec[secid].walls + i;
		rotsec->walls[i].x1 = (w->x1 - play->posx) * al->cos[angle] - (w->y1 -
			play->posy) * al->sin[angle];
		rotsec->walls[i].y1 = (w->x1 - play->posx) * al->sin[angle] + (w->y1 -
			play->posy) * al->cos[angle];
		rotsec->walls[i].x2 = (w->x2 - play->posx) * al->cos[angle] - (w->y2 -
			play->posy) * al->sin[angle];
		rotsec->walls[i].y2 = (w->x2 - play->posx) * al->sin[angle] + (w->y2 -
			play->posy) * al->cos[angle];
		i++;
	}
}

void		rot_ents(t_al *al, t_angle angle)
{
	unsigned	i;
	t_mob		*rotent;
	t_player	*play;

	rotent = al->rotent;
	play = &al->play;
	i = 0;
	while (i < al->nb_ent)
	{
		rotent[i].angle_to_player = (t_angle)(atan2(al->ent[i].posx -
			play->posx, al->ent[i].posy - play->posy) * D_2PI / M_2PI);
		al->ent[i].angle_to_player = rotent[i].angle_to_player;
		rotent[i].posx = (al->ent[i].posx - play->posx) * al->cos[angle] -
		(al->ent[i].posy - play->posy) * al->sin[angle];
		rotent[i].posy = (al->ent[i].posx - play->posx) * al->sin[angle] +
		(al->ent[i].posy - play->posy) * al->cos[angle];
		i++;
	}
}

/*
** Also cast entities
*/

void		set_floor_height(t_rc_hit *hit, t_sector *sec)
{
	hit->fl_tex = sec->fl_tex;
	hit->fl_hei = sec->fl_hei;
	hit->ce_tex = sec->ce_tex;
	hit->ce_hei = sec->ce_hei;
}

void		cast_sec(t_al *al, t_rc_ray *ray, unsigned secid, t_angle angle)
{
	unsigned	i;
	int			hits;
	int			enthits;
	t_sector	*rsec;

	set_floor_height(ray->hits + ray->nb_hits, al->sec + secid);
	rot_sec(al, secid, angle);
	rot_ents(al, angle);
	rsec = al->rotsec + secid;
	ray->min = INFINITY;
	ray->minent = INFINITY;
	ray->hits[ray->nb_hits].is_entity = 0;
	i = -1;
	enthits = 0;
	while (++i < al->nb_ent)
		enthits += test_ent_hit(al, ray, al->rotent + i, al->ent + i);
	i = -1;
	hits = 0;
	while (++i < rsec->nb_wal)
		hits += test_hit(al, ray, rsec->walls + i, al->sec[secid].walls + i);
	ray->nb_hits++;
	if (enthits && !hits)
		cast_sec(al, ray, secid, angle);
	else if (ray->hits[ray->nb_hits - 1].wall.sec_lnk)
		cast_sec(al, ray, ray->hits[ray->nb_hits - 1].wall.sec_lnk, angle);
}

void		cast_ray(t_al *al, t_angle an, t_rc_ray *ray)
{
	unsigned	i;

	i = 0;
	ray->angle = an & D_2PIM;
	ray->xfact = al->sin[ray->angle] * UINT16_MAX;
	ray->yfact = al->cos[ray->angle] * UINT16_MAX;
	cast_sec(al, ray, al->play.csec, ray->angle);
}
