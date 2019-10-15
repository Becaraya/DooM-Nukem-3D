/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/15 13:04:47 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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

int			test_aleready_hit(t_rc_ray *ray, t_walls *owall)
{
	int i;

	i = 0;
	while (i < ray->nb_hits)
	{
		//printf("\nwall1 [%4.1f,%4.1f %4.1f,%4.1f]   wall2 [%4.1f,%4.1f %4.1f,%4.1f]\n", owall->x1, owall->y1, owall->x2, owall->y2, ray->hits[i].wall.x1, ray->hits[i].wall.y1, ray->hits[i].wall.x2, ray->hits[i].wall.y2);
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

inline double	wall_len(t_walls *wall)
{
	double	tmp;

	tmp = (wall->x2 - wall->x1) * (wall->x2 - wall->x1);
	tmp += (wall->y2 - wall->y1) * (wall->y2 - wall->y1);
	return (sqrt(tmp));
}

void		test_hit(t_al *al, t_rc_ray *ray, t_walls *wall, t_walls *owall)
{
	double		alpha;
	double		beta;
	double		tmp_dst;
	double		min;

	min = INFINITY;
	if (((wall->x1 >= 0 && wall->x2 <= 0) ||
		(wall->x2 >= 0 && wall->x1 <= 0)) && wall->x1)
	{
		alpha = (wall->x2 - wall->x1) / (double)(wall->y2 - wall->y1);
		beta = wall->x1 - wall->y1 * alpha;
		if ((tmp_dst = -beta / alpha) > 0)
			if (tmp_dst < min)
				if (!test_aleready_hit(ray, owall))
				{
					ray->hits[ray->nb_hits].wall_length = wall_len(owall);
					wall->x1 > wall->x2 ? swapd(&wall->x1, &wall->x2) : 0;
					ray->hits[ray->nb_hits].hit_texx =
						(unsigned)(wall->x1 / (wall->x1 - wall->x2) * wall_len(owall) *
						UINT16_MAX) % (unsigned)(TEX_REPEAT * UINT16_MAX) / TEX_REPEAT;
					//!owall->sec_lnk ? printf("texx>%5u    wall [x1%4.1f  x2%4.1f]\n", ray->hits[ray->nb_hits].hit_texx, wall->x1, wall->x2) :0;
					tmp_dst *= al->cos[sub_angle(ray->angle, al->play.dir)];
					ray->hits[ray->nb_hits].hitdst = tmp_dst;
					ray->hits[ray->nb_hits].wall = *owall;
					min = ray->hits[ray->nb_hits].hitdst;
				}
	}
}

void		cast_sec(t_al *al, t_rc_ray *ray, unsigned secid, t_angle angle)
{
	unsigned	i;
	t_sector	*rsec;
	t_walls		*wall;

	i = -1;
	ray->hits[ray->nb_hits].fl_tex = al->sec[secid].fl_tex;
	ray->hits[ray->nb_hits].fl_hei = al->sec[secid].fl_hei;
	ray->hits[ray->nb_hits].ce_tex = al->sec[secid].ce_tex;
	ray->hits[ray->nb_hits].ce_hei = al->sec[secid].ce_hei;
	rot_sec(al, secid, angle);
	rsec = al->rotsec + secid;
	while (++i < rsec->nb_wal)
		test_hit(al, ray, rsec->walls + i, al->sec[secid].walls + i);
	//printf("hiiit a%3d  %d%+.1fm wallx%4.1f,y%4.1f  x%4.1f,y%4.1f\n", angle * 360 / D_2PI, ray->nb_hits, ray->hits[ray->nb_hits].hitdst, ray->hits[ray->nb_hits].wall.x1, ray->hits[ray->nb_hits].wall.y1, ray->hits[ray->nb_hits].wall.x2, ray->hits[ray->nb_hits].wall.y2);
	ray->nb_hits++;
	if (ray->hits[ray->nb_hits - 1].wall.sec_lnk)
		cast_sec(al, ray, ray->hits[ray->nb_hits - 1].wall.sec_lnk, angle);
}






void		cast_ray(t_al *al, int x, t_rc_ray *ray)
{
	unsigned	i;
	int			tmp_angle;

	i = 0;
	tmp_angle = al->play.dir + ((int)al->fov * (x - (WIN_SIZEX / 2))
		/ WIN_SIZEX);
	while (tmp_angle < 0)
		tmp_angle += D_2PI;
	ray->angle = tmp_angle & D_2PIM;
	cast_sec(al, ray, al->play.csec, ray->angle);
}








void		render(t_al *al)
{
	t_rc_ray	ray;
	int			x;

	if (al->play.horizon < -HORIZON_LIMIT || al->play.horizon > HORIZON_LIMIT)
	{
		pr_err("Off-range horizon\n");
		return ;
	}
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	x = 0;
	while (x < WIN_SIZEX)
	{
		ray.angle = 0;
		ray.nb_hits = 0;
		cast_ray(al, x, &ray);
		column(al, x, &ray);
		x++;
	}
	/*ray.nb_hits = 0;
	cast_ray(al, WIN_SIZEX / 2, &ray);
	while (x < WIN_SIZEX)
	{
		column(al, x, &ray);
		x++;
	}*/
	printf("FPS:%2d ", 1000000 / al->dtime); fflush(0);
	SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int));
	SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0);
	SDL_RenderPresent(al->sdlren);
}
