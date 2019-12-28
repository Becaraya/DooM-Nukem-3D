/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_linesaver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 03:17:58 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

inline void	hit_wall_heights(t_al *al, t_rc_hit *hit, t_rc_lim *lim, int hor)
{
	hit->wall_he = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
	lim->topwall = hor - ((hit->ce_hei - al->play.eyez) *
		al->wall_scale / hit->hitdst);
	lim->topmid = lim->topwall;
	lim->botwall = hor + ((al->play.eyez - hit->fl_hei) *
		al->wall_scale / hit->hitdst);
	lim->botmid = lim->botwall;
}

inline void	hit_next_walls(t_al *al, t_rc_hit *hit, t_rc_lim *lim, int hor)
{
	hit->wall_he = new_wall_he(hit, hit + 1);
	lim->topmid = hit->ce_hei > (hit + 1)->ce_hei ? hor -
	((hit + 1)->ce_hei - al->play.eyez) * al->wall_scale / hit->hitdst
	: lim->topwall;
	hit->topwall_he = hit->ce_hei > (hit + 1)->ce_hei ? (hit->ce_hei -
	(hit + 1)->ce_hei) * UINT16_MAX : 0;
	lim->botmid = hit->fl_hei < (hit + 1)->fl_hei ? hor +
	(al->play.eyez - (hit + 1)->fl_hei) * al->wall_scale / hit->hitdst
	: lim->botwall;
	hit->botwall_he = hit->fl_hei < (hit + 1)->fl_hei ?
	((hit + 1)->fl_hei - hit->fl_hei) * UINT16_MAX : 0;
}

inline void	hit_linesave_ent(t_al *al, t_rc_hit *hit, t_rc_lim *lim, int hor)
{
	lim->topmid = hor + ((al->play.eyez - (hit->ent.posz + hit->ent.size)) *
		al->wall_scale / hit->hitdst);
	lim->botmid = hor - ((hit->ent.posz - al->play.eyez) *
		al->wall_scale / hit->hitdst);
}
