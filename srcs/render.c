/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2019/11/25 15:16:49 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		draw_map(t_al *al)
{
	t_point a;
	t_point b;
	unsigned int nb_wal;
	unsigned int nb_sec;

	nb_sec = 1;
	while (nb_sec <= al->nb_sec)
	{
		nb_wal = 0;
		while (nb_wal < al->sec[nb_sec].nb_wal)
		{
			a.x = al->sec[nb_sec].walls[nb_wal].x1 * 10 + (WIN_SIZEX / 2);
			a.y = -al->sec[nb_sec].walls[nb_wal].y1 * 10 + (WIN_SIZEY / 2);
			b.x = al->sec[nb_sec].walls[nb_wal].x2 * 10 + (WIN_SIZEX / 2);
			b.y = -al->sec[nb_sec].walls[nb_wal].y2 * 10 + (WIN_SIZEY / 2);
			//printf("xxxx%d,%d,%d,%dxxxxx",a.x,a.y,b.x,b.y);
			ft_put_line(a, b, al->sdlsurf, WHITE);
			nb_wal++;
		}
		nb_sec++;
	}
	//a.y = -al->ent[0].posy * 10 + (WIN_SIZEY / 2);
	//a.x = al->ent[0].posx * 10 + (WIN_SIZEX / 2);
	b.y = a.y + 5;
	b.x = a.x + 5;
	while(++a.y < b.y)
	{
		//a.x = al->ent[0].posx * 10 + (WIN_SIZEX / 2);
		while(++a.x < b.x)
			al->pix[(int)(a.x + (a.y * WIN_SIZEX))] = 0x0000ff;
	}
	
	a.x = al->play.posx * 10 + (WIN_SIZEX / 2);
	a.y = -al->play.posy * 10 + (WIN_SIZEY / 2);
	b.x = a.x + al->sin[al->play.dir] * 10;
	b.y = a.y - al->cos[al->play.dir] * 10;
	ft_put_line(a, b, al->sdlsurf, WHITE);
	al->pix[(int)(a.x + (a.y * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + 1 + (a.y * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + ((a.y + 1) * WIN_SIZEX))] = 0xff00ff;
	al->pix[(int)(a.x + 1 + ((a.y + 1) * WIN_SIZEX))] = 0xff00ff;
}

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
		//printf("%f,%f %f,%f\n", rotsec->walls[i].x1 + play->posx, rotsec->walls[i].y1 + play->posy, rotsec->walls[i].x2 + play->posx, rotsec->walls[i].y2+ + play->posy);
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
		rotent[i].posx = (al->ent[i].posx - play->posx) * al->cos[angle] -
		(al->ent[i].posy - play->posy) * al->sin[angle];
		rotent[i].posy = (al->ent[i].posx - play->posx) * al->sin[angle] +
		(al->ent[i].posy - play->posy) * al->cos[angle];
		//angle == al->play.dir ? printf("   x%.1f y%.2f\n", rotent[i].posx, rotent[i].posy):0;
		i++;
	}
}

inline t_angle	d_atan2(double d1, double d2)
{
	d1 = atan2(d1, d2);
	d1 = d1 < 0 ? M_2PI + d1 : d1;
	return ((t_angle)(d1 * D_2PI / M_2PI));
}

inline t_angle	d_atan(double a)
{
	a = atan(a);
	a = a < 0 ? M_2PI + a : a;
	return ((t_angle)(a * D_2PI / M_2PI));
}

void		swapd(double *d1, double *d2)
{
	double tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

double		wall_len(t_walls *wall)
{
	double	tmp;

	tmp = (wall->x2 - wall->x1) * (wall->x2 - wall->x1);
	tmp += (wall->y2 - wall->y1) * (wall->y2 - wall->y1);
	return (sqrt(tmp));
}

int			test_aleready_hit(t_rc_ray *ray, t_walls *owall)
{
	int i;

	i = 0;
	while (i < ray->nb_hits)
	{
		//printf("\nwall1 [%4.1f,%4.1f %4.1f,%4.1f]   wall2 [%4.1f,%4.1f %4.1f,%4.1f]\n", owall->x1, owall->y1, owall->x2, owall->y2, ray->hits[i].wall.x1, ray->hits[i].wall.y1, ray->hits[i].wall.x2, ray->hits[i].wall.y2);
		if (!ray->hits[i].is_entity)
			if ((ray->hits[i].wall.x1 == owall->x1 &&
					ray->hits[i].wall.y1 == owall->y1 &&
					ray->hits[i].wall.x2 == owall->x2 &&
					ray->hits[i].wall.y2 == owall->y2) ||
				(ray->hits[i].wall.x1 == owall->x2 &&
					ray->hits[i].wall.y1 == owall->y2 &&
					ray->hits[i].wall.x2 == owall->x1 &&
					ray->hits[i].wall.y2 == owall->y1))
				return (1);
		i++;
	}
	return (0);
}

int			test_ent_aleready_hit(t_rc_ray *ray, t_mob *oent)
{
	int i;

	i = 0;
	while (i < ray->nb_hits)
	{
		//printf("\n i>%d\tent1 [x%4.1f y%4.1f z%4.1f]   ent2 [x%4.1f y%4.1f z%4.1f]\n", i, ray->hits[i].ent.posx, ray->hits[i].ent.posy, ray->hits[i].ent.posz, oent->posx, oent->posy, oent->posz);
		if (ray->hits[i].is_entity)
			if (ray->hits[i].ent.posx == oent->posx &&
				ray->hits[i].ent.posy == oent->posy &&
				ray->hits[i].ent.posz == oent->posz)
				return (1);
		i++;
	}
	return (0);
}

int			test_hit(t_al *al, t_rc_ray *ray, t_walls *wall, t_walls *owall)
{
	double		alpha;
	double		beta;
	double		tmp_dst;

	if (((wall->x1 >= 0 && wall->x2 <= 0) ||
		(wall->x2 >= 0 && wall->x1 <= 0)) && wall->x1)
	{
		alpha = (wall->x2 - wall->x1) / (double)(wall->y2 - wall->y1);
		beta = wall->x1 - wall->y1 * alpha;
		tmp_dst = wall->y2 == wall->y1 ? 0 : -beta / alpha;
		if (tmp_dst > 0 && tmp_dst < ray->min)
			if (!test_aleready_hit(ray, owall))
			{
				ray->min = tmp_dst;
				ray->hits[ray->nb_hits].is_entity = 0;
				ray->hits[ray->nb_hits].wall_length = wall_len(owall);
				wall->x1 > wall->x2 ? swapd(&wall->x1, &wall->x2) : 0;
				ray->hits[ray->nb_hits].hit_texx = (unsigned)(wall->x1 /
					(wall->x1 - wall->x2) * wall_len(owall) * UINT16_MAX) %
					(unsigned)(TEX_REPEAT * UINT16_MAX) / TEX_REPEAT;
				tmp_dst *= al->cos[sub_angle(ray->angle, al->play.dir)];
				ray->hits[ray->nb_hits].hitdst = tmp_dst;
				ray->hits[ray->nb_hits].wall = *owall;
				ray->hits[ray->nb_hits].tex = al->tex[owall->wall_tex];
				return (1);
			}
	}
	return (0);
}

int			test_ent_hit(t_al *al, t_rc_ray *ray, t_mob *rotent, t_mob *oent)
{
	if (rotent->posx < oent->width / 2 && rotent->posx > -oent->width / 2)
	{
		if (rotent->posy > 0 && rotent->posy < ray->min && rotent->posy <
			ray->minent)
			if (!test_ent_aleready_hit(ray, oent))
			{
				ray->minent = rotent->posy;
				ray->min = rotent->posy;
				ray->hits[ray->nb_hits].is_entity = 1;
				ray->hits[ray->nb_hits].wall_length = oent->width;
				//wall->x1 > wall->x2 ? swapd(&wall->x1, &wall->x2) : 0;
				//	ray->hits[ray->nb_hits].hit_texx = (unsigned)(wall->x1 /
				//	(wall->x1 - wall->x2) * wall_len(owall) * UINT16_MAX) %
				//	(unsigned)(TEX_REPEAT * UINT16_MAX) / TEX_REPEAT;
				ray->hits[ray->nb_hits].hitdst = rotent->posy * al->cos[sub_angle(
						ray->angle, al->play.dir)];
				ray->hits[ray->nb_hits].ent = *oent;
				ray->hits[ray->nb_hits].tex = al->tex[1];
				return (1);
			}
		}
	return (0);
}

/*
** Also cast entites
*/

void		cast_sec(t_al *al, t_rc_ray *ray, unsigned secid, t_angle angle)
{
	unsigned	i;
	int			hits;
	int			enthits;
	t_sector	*rsec;

	ray->hits[ray->nb_hits].fl_tex = al->sec[secid].fl_tex;
	ray->hits[ray->nb_hits].fl_hei = al->sec[secid].fl_hei;
	ray->hits[ray->nb_hits].ce_tex = al->sec[secid].ce_tex;
	ray->hits[ray->nb_hits].ce_hei = al->sec[secid].ce_hei;
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

void		invert_pix(unsigned int *pix)
{
	*pix = ~(*pix);
}

void		pimp_cross(t_al *al)
{
	int i;

	i = WIN_SIZEY / 2 - 12;
	while (i <= WIN_SIZEY / 2 + 12)
	{
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2 - 1);
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2);
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2 + 1);
		i++;
	}
	i = WIN_SIZEX / 2 - 12;
	while (i <= WIN_SIZEX / 2 + 12)
	{
		if (i < WIN_SIZEX / 2 - 1 || i > WIN_SIZEX / 2 + 1)
		{
			invert_pix(al->pix + WIN_SIZEX * (WIN_SIZEY / 2 - 1) + i);
			invert_pix(al->pix + WIN_SIZEX * WIN_SIZEY / 2 + i);
			invert_pix(al->pix + WIN_SIZEX * (WIN_SIZEY / 2 + 1) + i);
		}
		i++;
	}
}

void		render(t_al *al)
{
	t_rc_ray	ray;
	int			x;

	al->wall_scale = 0.1624 * D_2PI / al->fovn;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	x = 0;
	while (x < WIN_SIZEX)
	{
		ray.nb_hits = 0;
		ray.x = x;
		cast_ray(al, (t_angle)(atan(al->fovn * (x - (WIN_SIZEX / 2)) /
					WIN_SIZEX) / M_2PI * D_2PI + al->play.dir) & D_2PIM, &ray);
		column(al, &ray);
		x++;
	}
	pimp_cross(al);
	/*ray.nb_hits = 0;
	cast_ray(al, (t_angle)(atan(al->fovn * (x - (WIN_SIZEX / 2)) /
		WIN_SIZEX) / M_2PI * D_2PI + al->play.dir) & D_2PIM, &ray);
	while (x < WIN_SIZEX)
	{
		column(al, x, &ray);
		x++;
	}*/
	//draw_map(al);
	ft_putstr(" FPS:");
	ft_putnbr(1000000 / al->dtime);
	refresh(al);
}
