/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/30 11:31:39 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** je noie ma souffrance dans l'alcool
*/

void		sc_lims(t_rc_lim *lim, t_rc_lim prlim)
{
	lim->sc_toplim = lim->toplim;
	cap_int(&lim->sc_toplim, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_topwall = lim->topwall;
	cap_int(&lim->sc_topwall, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_topmid = lim->topmid;
	cap_int(&lim->sc_topmid, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_botlim = lim->botlim;
	cap_int(&lim->sc_botlim, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_botwall = lim->botwall;
	cap_int(&lim->sc_botwall, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_botmid = lim->botmid;
	cap_int(&lim->sc_botmid, prlim.mb_toplim, prlim.mb_botlim);
	lim->mb_toplim = lim->sc_topmid;
	lim->mb_botlim = lim->sc_botmid;
}

void		hit_ent(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	tex = &ray->hits[hitnb].tex;
	lim = &ray->hits[hitnb].lim;
	tot_length = lim->botmid - lim->topmid;
	y = lim->sc_topmid;
	while (y < lim->sc_botmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx,
		(y - lim->topmid) * tex->size_y / tot_length, tex);
		y -= -1;
	}
}

unsigned	new_wall_he(t_rc_hit *hit, t_rc_hit *nhit)
{
	double ceil;
	double floor;

	ceil = hit->ce_hei > nhit->ce_hei ? nhit->ce_hei : hit->ce_hei;
	floor = hit->fl_hei < nhit->fl_hei ? nhit->fl_hei : hit->fl_hei;
	return ((unsigned)((ceil - floor) * UINT16_MAX));
}

void		hit_print(t_al *al, t_rc_ray *ray, int hitnb, t_rc_lim prlim)
{
	t_rc_hit	*hit;
	t_rc_lim	*lim;
	int			hor;

	hit = ray->hits + hitnb;
	lim = &hit->lim;
	hor = WIN_SIZEY / 2 - al->play.horizon;
	if (!hit->is_entity)
	{
		lim->toplim = prlim.mb_toplim;
		lim->botlim = prlim.mb_botlim;
		hit_wall_heights(al, hit, lim, hor);
		if (hitnb < ray->nb_hits - 1)
			hit_next_walls(al, hit, lim, hor);
		sc_lims(lim, prlim);
		hit_ceiling(al, ray, hitnb);
		hit_floor(al, ray, hitnb);
		if (hitnb < ray->nb_hits - 1)
			hit_top_bot_wall(al, ray, hitnb);
	}
	hit->is_entity ? hit_linesave_ent(al, hit, lim, hor) : 0;
	hit->is_entity ? sc_lims(lim, prlim) : 0;
	if (hitnb < ray->nb_hits - 1)
		hit_print(al, ray, hitnb + 1, hit->is_entity ? prlim : *lim);
	hit->is_entity ? hit_ent(al, ray, hitnb) : hit_wall(al, ray, hitnb);
}

void		column(t_al *al, t_rc_ray *ray)
{
	t_rc_lim lim;

	lim.mb_toplim = 0;
	lim.mb_botlim = WIN_SIZEY - 1;
	hit_print(al, ray, 0, lim);
}
