/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/25 10:54:24 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		init_wall(t_al *al)
{
	if (!(al->wall = (t_wall *)ft_memalloc(sizeof(t_wall))))
		yeet(al);
	al->wall->next = NULL;
	al->wall->prev = NULL;
}

static void		init_status(t_al *al)
{
	al->stat_fnc[MENU] = menu;
	al->stat_fnc[GAME] = game;
	al->stat_fnc[PAUSE] = yeet; // to dew
	al->stat_fnc[EDIT] = editor;
}

static void		init_player(t_al *al, t_player *pl)
{
	pl->mass = PLAYER_MASS;
	pl->power = PLAYER_AERO_POWER;
	pl->power_mult = 1;
	pl->size = PLAYER_SIZE;
	pl->on_ground = 1;
	pl->posz = al->sec[1].fl_hei;
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);
	init_status(al);
	al->status = GAME;
	al->fps = 60;
	al->edit.stat = T_WALL_IDLE;
	al->c_wall = 0; // bzero init everything to 0, this func is for !0 inits ;)
	al->edit.zoom = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->sdlwin = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
			WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if ((al->sdlren = SDL_CreateRenderer(al->sdlwin, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
		yeet(al);
	if ((al->sdltex = SDL_CreateTexture(al->sdlren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC, WIN_SIZEX, WIN_SIZEY)) == NULL)
		yeet(al);
	if ((al->pix = ft_memalloc(WIN_SIZEX * WIN_SIZEY * sizeof(int))) == NULL)
		exit(pr_err(MERROR_MESS));
	init_wall(al);
	init_player(al, &al->play);
	al->g = DEFAULT_G;
	al->fov = DEFAULT_FOV;
}
