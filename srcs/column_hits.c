/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_hits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 23:42:13 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 15:48:29 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		hit_floor(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_floorcast	f;
	t_tex		*tex;
	int			y;
	long		tmp;

	tex = al->tex + ray->hits[hitnb].fl_tex;
	y = ray->hits[hitnb].lim.sc_botwall;
	f.posx = al->play.posx * UINT16_MAX * al->fov;
	f.posy = al->play.posy * UINT16_MAX * al->fov;
	f.hor = al->play.horizon + HORIZON_LIMIT;
	f.indst = UINT16_MAX * (al->play.eyez - ray->hits[hitnb].fl_hei) *
	al->stretch / al->cos[sub_angle(ray->angle, al->play.dir)];
	while (y < ray->hits[hitnb].lim.sc_botlim)
	{
		tmp = (2 * (y + f.hor) - al->stretch);
		tmp = tmp ? f.indst / tmp : UINT16_MAX;
		f.dstx = tmp * ray->xfact / UINT16_MAX + f.posx * 1.04;
		f.dsty = tmp * ray->yfact / UINT16_MAX + f.posy * 1.04;
		f.dstx = ((f.dstx & TEX_REPEAT_F) * tex->size_x) >> TEX_REPEAT_F_DIV;
		f.dsty = ((f.dsty & TEX_REPEAT_F) * tex->size_y) >> TEX_REPEAT_F_DIV;
		tmp = f.dsty * tex->size_x + f.dstx;
		al->pix[y * WIN_SIZEX + ray->x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp]
		: skybox(al, y, 0);
		y -= -1;
	}
}

void		hit_ceiling(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_floorcast	f;
	t_tex		*tex;
	int			y;
	long		tmp;

	tex = al->tex + ray->hits[hitnb].ce_tex;
	y = ray->hits[hitnb].lim.sc_toplim;
	f.posx = al->play.posx * UINT16_MAX * al->fov;
	f.posy = al->play.posy * UINT16_MAX * al->fov;
	f.hor = al->play.horizon + HORIZON_LIMIT;
	f.indst = UINT16_MAX * (ray->hits[hitnb].ce_hei - al->play.eyez) *
	al->stretch / al->cos[sub_angle(ray->angle, al->play.dir)];
	while (y < ray->hits[hitnb].lim.sc_topwall)
	{
		tmp = al->stretch - 2 * (y + f.hor);
		tmp = tmp ? f.indst / tmp : UINT16_MAX;
		f.dstx = tmp * ray->xfact / UINT16_MAX + f.posx * 1.04;
		f.dsty = tmp * ray->yfact / UINT16_MAX + f.posy * 1.04;
		f.dstx = ((f.dstx & TEX_REPEAT_F) * tex->size_x) >> TEX_REPEAT_F_DIV;
		f.dsty = ((f.dsty & TEX_REPEAT_F) * tex->size_y) >> TEX_REPEAT_F_DIV;
		tmp = f.dsty * tex->size_x + f.dstx;
		al->pix[y * WIN_SIZEX + ray->x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp]
		: skybox(al, y, 0);
		y -= -1;
	}
}

void		hit_bot_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->botwall - lim->botmid;
	y = lim->sc_botmid;
	while (y < lim->sc_botwall)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->botmid) * hit->botwall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y -= -1;
	}
}

void		hit_top_bot_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->topmid - lim->topwall;
	y = lim->sc_topwall;
	while (y < lim->sc_topmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->topwall) * hit->topwall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y -= -1;
	}
	hit_bot_wall(al, ray, hitnb);
}

void		hit_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	if (hit->transparent)
		return ;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->botmid - lim->topmid;
	y = lim->sc_topmid;
	while (y < lim->sc_botmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->topmid) * hit->wall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y -= -1;
	}
}
