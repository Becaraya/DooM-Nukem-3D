/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:44:07 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 11:44:18 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		init_status(t_al *al)
{
	al->stat_fnc[MENU] = menu;
	al->stat_fnc[GAME] = game;
	al->stat_fnc[DEAD] = dead;
	al->stat_fnc[PAUSE] = yeet;
	al->stat_fnc[EDIT] = editor;
}

void		init_player(t_al *al, t_player *pl)
{
	pl->mass = PLAYER_MASS;
	pl->power = PLAYER_AERO_POWER;
	pl->power_mult = 1;
	pl->size = PLAYER_SIZE;
	pl->eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
	pl->on_ground = 1;
	pl->alive = 5;
	pl->dmg = 6;
	pl->csec ? pl->posz = al->sec[pl->csec].fl_hei : 0;
}

void		init_trigo(t_al *al)
{
	int				i;

	i = 0;
	while (i < D_2PI)
	{
		al->sin[i] = sin(M_2PI * i / D_2PI);
		i++;
	}
	i = 0;
	while (i < D_2PI)
	{
		al->cos[i] = cos(M_2PI * i / D_2PI);
		i++;
	}
}

t_mob		*new_m(t_al *al, SDL_MouseButtonEvent bev, unsigned i)
{
	t_mob	*data;

	if (!(data = malloc(sizeof(t_mob))))
		yeet(al);
	bzerooo(data, sizeof(t_mob));
	data->posx = (bev.x - WIN_SIZEX / 2) / 10.0;
	data->posy = (bev.y - WIN_SIZEY / 2) / -10.0;
	data->index = i;
	data->next = NULL;
	return (data);
}

void		init_edit(t_al *al)
{
	if (!(al->win_ed = SDL_CreateWindow(WIN_TITLE, WIN_POSX + WIN_SIZEX,
		WIN_POSY, WIN_EDIT_SIZEX, WIN_EDIT_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->surf_ed = SDL_GetWindowSurface(al->win_ed)))
		yeet(al);
	al->pix_ed = al->surf_ed->pixels;
	init_text_edit(al);
}
