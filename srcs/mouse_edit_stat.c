/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit_stat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:31:24 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/04 16:30:55 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	mouse_press_edit_mini_menu(t_al *al, SDL_MouseButtonEvent bev)
{
	if (inr(itop(495, 540), itop(645, 585), itop(bev.x, bev.y)))
		al->edit.stat = SELECT;
	if (al->sect)
	{
		if (inr(itop(45, 605), itop(220, 650), itop(bev.x, bev.y)))
		{
			link_sectors(al);
			ft_putstr("Sector linked !\n");
			al->edit.stat = SELECT;
		}
		if (inr(itop(45, 540), itop(220, 585), itop(bev.x, bev.y)))
			al->edit.stat = (al->edit.stat != SET_SPAWN) ? SET_SPAWN : SET_END;
		if (inr(itop(280, 540), itop(460, 585), itop(bev.x, bev.y)))
			al->edit.stat = SET_BAD_PIG;
		if (inr(itop(45, 240), itop(220, 285), itop(bev.x, bev.y)))
			al->edit.stat = EDIT_SECT;
		if (inr(itop(280, 240), itop(460, 285), itop(bev.x, bev.y)))
			al->edit.stat = EDIT_WALL;
		if (inr(itop(495, 240), itop(645, 285), itop(bev.x, bev.y)))
			al->edit.stat = SET_PLAYER;
		if (inr(itop(280, 605), itop(460, 650), itop(bev.x, bev.y)))
			al->edit.stat = GRAVITY;
	}
}

void	mouse_press_edit_setting_sector(t_al *al, SDL_MouseButtonEvent bev)
{
	if (al->edit.stat >= SET_FLO_TEXT && al->edit.stat <= EDIT_SECT)
	{
		if (inr(itop(45, 400), itop(220, 445), itop(bev.x, bev.y)))
			al->edit.stat = SET_FLO_HEI;
		if (inr(itop(45, 320), itop(220, 365), itop(bev.x, bev.y)))
			al->edit.stat =
			(al->edit.stat == EDIT_WALL) ? SET_WALL_TEXT : SET_FLO_TEXT;
		if (inr(itop(280, 400), itop(460, 445), itop(bev.x, bev.y)))
			al->edit.stat = SET_CEL_HEI;
		if (inr(itop(280, 320), itop(460, 365), itop(bev.x, bev.y)))
			al->edit.stat = SET_CEL_TEXT;
		if (inr(itop(495, 320), itop(645, 365), itop(bev.x, bev.y)))
			al->door = al->nb_sec - al->edit.index_sect + 1;
	}
}

void	mouse_press_edit_player(t_al *al, SDL_MouseButtonEvent bev)
{
	if (al->edit.stat >= SET_PLAYER && al->edit.stat <= MASS)
	{
		if (inr(itop(45, 320), itop(220, 365), itop(bev.x, bev.y)))
			al->edit.stat = LIFE;
		if (inr(itop(280, 320), itop(460, 365), itop(bev.x, bev.y)))
			al->edit.stat = POW;
		if (inr(itop(495, 320), itop(645, 365), itop(bev.x, bev.y)))
			al->edit.stat = WEAPON;
		if (inr(itop(45, 400), itop(220, 445), itop(bev.x, bev.y)))
			al->edit.stat = SIZE;
		if (inr(itop(280, 400), itop(460, 445), itop(bev.x, bev.y)))
			al->edit.stat = MASS;
	}
}
