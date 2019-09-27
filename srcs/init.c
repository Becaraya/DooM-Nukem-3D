/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/27 17:41:54 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		init_wall(t_al *al)
{
	if (!(al->wall = (t_wall *)ft_memalloc(sizeof(t_wall))))
		yeet(al);
	al->wall->next = NULL;
	al->wall->prev = NULL;
	al->wall->x1 = -1;
	al->wall->x2 = -1;
	al->wall->y1 = -1;
	al->wall->y2 = -1;
}

static void		init_status(t_al *al)
{
	al->stat_fnc[MENU] = menu;
	al->stat_fnc[GAME] = game;
	al->stat_fnc[PAUSE] = yeet;
	al->stat_fnc[EDIT] = editor;
}

static void		init_player(t_al *al, t_player *pl)
{
	pl->mass = PLAYER_MASS;
	pl->power = PLAYER_AERO_POWER;
	pl->power_mult = 1;
	pl->size = PLAYER_SIZE;
	pl->on_ground = 1;
	pl->posz = pl->csec->fl_hei;
}

static void		init_edit(t_al *al)
{
	// if (SDL_Init(SDL_INIT_VIDEO) < 0)
	// 	yeet(al); supposed to be useless because theres aleready one in the main init
	if (!(al->win_ = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY, WIN_SIZEX,
				WIN_SIZEY, SDL_WINDOW_RESIZABLE)))
		yeet(al);
	if ((al->ren_ = SDL_CreateRenderer(al->win_, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC)) == NULL)
		yeet(al);
	if ((al->tex_ = SDL_CreateTexture(al->ren_, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC, WIN_SIZEX, WIN_SIZEY)) == NULL)
		yeet(al);
	if ((al->pix_ = ft_memalloc(WIN_SIZEX * WIN_SIZEY * sizeof(int))) == NULL)
		yeet(al);
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);
	init_player(al, &al->play);
	init_status(al);
	al->status = GAME;
	// al->status = EDIT;
	al->fps = 60;
	al->g = DEFAULT_G;
	al->fov = DEFAULT_FOV;

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
	ft_bzero(&al->k, sizeof(t_keys));
	al->edit.stat = RECTANGLE_SELECT; // al->edit.stat = FIRST_CLICK;
	al->edit.zoom = 15;
	al->c_wall = 0; // bzero init everything to 0, this func is for !0 inits ;)
}
