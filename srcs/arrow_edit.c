/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:55:47 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/27 15:50:02 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void			arrow_stat_hei(t_al *al, SDL_MouseButtonEvent bev)
{
	t_sector	*tmp;
	int			i;

	i = 0;
	tmp = al->sect;
	while (al->edit.index_sect + i++ < al->nb_sec)
		tmp = tmp->next;
	if (al->edit.stat == SET_CEL_HEI)
	{
		if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435
		&& tmp->ce_hei > tmp->fl_hei && tmp->ce_hei)
			tmp->ce_hei -= 0.25;
		if (inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y)))
			tmp->ce_hei += 0.25;
	}
	if (al->edit.stat == SET_FLO_HEI)
	{
		if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435
		&& tmp->fl_hei > 0)
			tmp->fl_hei -= 0.25;
		if (inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y))
		&& tmp->ce_hei > tmp->fl_hei)
			tmp->fl_hei += 0.25;
	}
}

static void			arrow_stat_player(t_al *al, t_point bev)
{
	if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435)
		arrow_stat_player_minus(al);
	if (inr(itop(630, 410), itop(660, 435), bev))
		arrow_stat_player_plus(al);
}

static void			arrow_gravity(t_al *al, SDL_MouseButtonEvent bev)
{
	if (inr(itop(520, 625), itop(545, 660), itop(bev.x, bev.y)) && al->g > 2)
	{
		if (al->g == DEFAULT_G)
			al->g = 9.0;
		else
			al->g--;
	}
	if (inr(itop(630, 615), itop(660, 660), itop(bev.x, bev.y)))
	{
		if (al->g == DEFAULT_G)
			al->g = 10.0;
		else
			al->g++;
	}
	(al->text.g_num.str) ? ft_strdel(&al->text.g_num.str) : 0;
	al->text.g_num.str = dtoa_doom(al->g);
}

void				arrow_stat(t_al *al, SDL_MouseButtonEvent bev)
{
	if (al->edit.index_sect > 1 && bev.x > 145 && bev.x < 175
		&& bev.y > 15 && bev.y < 47)
	{
		!(al->edit.index_wall = 0) ? al->edit.index_sect-- : 0;
		al->edit.stat = SELECT;
	}
	if (al->edit.index_sect < al->nb_sec && bev.x > 176 && bev.x < 195
		&& bev.y > 15 && bev.y < 47)
	{
		!(al->edit.index_wall = 0) ? al->edit.index_sect++ : 0;
		al->edit.stat = SELECT;
	}
	if (al->edit.index_wall > 0 && bev.x > 145 && bev.x < 175
		&& bev.y > 59 && bev.y < 86)
		al->edit.index_wall--;
	if (al->edit.index_wall < nb_wall(al) - 1
		&& bev.x > 176 && bev.x < 195 && bev.y > 59 && bev.y < 86)
		al->edit.index_wall++;
	if (al->edit.stat == SET_CEL_HEI || al->edit.stat == SET_FLO_HEI)
		arrow_stat_hei(al, bev);
	if (al->edit.stat >= LIFE && al->edit.stat <= MASS)
		arrow_stat_player(al, itop(bev.x, bev.y));
	if (al->edit.stat == GRAVITY)
		arrow_gravity(al, bev);
}
