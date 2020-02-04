/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/04 12:08:33 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	set_default_player(t_al *al)
{
	al->g = DEFAULT_G;
	al->play.mass = PLAYER_MASS;
	al->play.power_mult = 1;
	al->play.size = PLAYER_SIZE;
	al->play.eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
	al->play.alive = 10;
}

void	m_press_ed_glob_n_arr(t_al *al, SDL_MouseButtonEvent bev)
{
	arrow_stat(al, bev);
	mouse_press_edit_mini_menu(al, bev);
	mouse_press_edit_setting_sector(al, bev);
	mouse_press_edit_player(al, bev);
}

void	reset_map(t_al *al)
{
	free_sect(al->sect);
	al->sect = NULL;
	al->nb_sec = 0;
	al->edit.index_sect = 0;
	al->edit.index_wall = 0;
}

void	mouse_press_edit_menu(t_al *al, SDL_MouseButtonEvent bev)
{
	if (al->edit.stat == DRAWING)
	{
		if (bev.x > 590 && bev.x < 685 && bev.y > 15 && bev.y < 48)
		{
			al->edit.stat = SELECT;
			free_wall(al->sect->walls);
			al->nb_sec--;
			delonesect(&al->sect);
		}
	}
	else
		m_press_ed_glob_n_arr(al, bev);
	if (inr(itop(45, 125), itop(230, 170), itop(bev.x, bev.y)))
		al->hard = !al->hard;
	if (inr(itop(280, 125), itop(460, 170), itop(bev.x, bev.y))
		&& al->edit.stat != DRAWING && al->sect)
		reset_map(al);
	if (inr(itop(495, 125), itop(645, 170), itop(bev.x, bev.y)))
		set_default_player(al);
	if (inr(itop(280, 655), itop(493, 698), itop(bev.x, bev.y)))
		edit_to_game(al);
}

void	mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	if (bev.windowID == 1)
	{
		if (al->edit.stat == SET_SPAWN)
			set_spawn(al, bev);
		if (al->edit.stat == SET_END)
			set_end(al, bev);
		if (al->edit.stat == SET_BAD_PIG)
			badpig(al, bev);
		if (al->edit.stat == SELECT)
		{
			al->edit.stat = DRAWING;
			al->nb_sec++;
			al->edit.index_wall = 1;
			add_sector(al, itop(bev.x, bev.y));
		}
		else if (al->edit.stat == DRAWING)
			check_can_add(al, al->sect, itop(bev.x, bev.y));
	}
	if (bev.windowID == 2)
		mouse_press_edit_menu(al, bev);
}
