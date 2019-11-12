/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/12 18:34:18 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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
	pl->eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
	pl->on_ground = 1;
	pl->alive = 0;
	pl->posz = al->sec[pl->csec].fl_hei;
}

/*
** je sait pas ou ranger cette fonction
*/

void    		creat_entity(t_al *al)
{
	al->ent.posx = 2;
    al->ent.posy = 2;
	al->ent.csec = 1;
	al->ent.vely = 0.1;
	al->ent.size = PLAYER_SIZE;
	al->ent.on_ground = 1;
	al->ent.dir = 1500;
	al->ent.gd_vel = 2.5;
	al->ent.power = 400;
	al->ent.power_mult = 1;
	al->ent.mass = 67;
	al->ent.alive = 1;
	al->ent.posz = al->sec[al->play.csec].fl_hei;
}

static void		init_trigo(t_al *al)
{
	int i;

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
	/*i = 0;
	while (i < D_2PI)
	{
		al->tan[i] = tan(M_2PI * i / D_2PI);
		i++;
	}*/
}

void			init_ttf(t_al *al)
{
	al->ttf_st = (!TTF_Init()) ? 1 : 0;
	if (!(al->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		yeet(al);
	
}

int				set_text(t_text *text, char *str, SDL_Rect coo, SDL_Color clr) 
{
	if (!(text->str = ft_strdup(str)))
		return (-1);
	if (!(text->where = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect))))
		return (-1);
	text->where->x = coo.x;
	text->where->y = coo.y;
	ft_memcpy(&text->clr, &clr, sizeof(&clr));
	return (0); 
}

static void		init_edit(t_al *al)
{
	if (!(al->win_ed = SDL_CreateWindow(WIN_TITLE, WIN_POSX + WIN_SIZEX,
		WIN_POSY, WIN_EDIT_SIZEX, WIN_EDIT_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->surf_ed = SDL_GetWindowSurface(al->win_ed)))
		yeet(al);
	al->pix_ed = al->sdlsurf->pixels;

	/*
	** ALL TEXT EDITOR
	*/

	set_text(&al->text.gen_map, "GENERATION MAP", get_rect(300, 700), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.sect_para, "WHO", get_rect(25, 20), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;

	set_text(&al->text.x_start, "X1", get_rect(25, 50), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.y_start, "Y1", get_rect(150, 50), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.x_end, "X2", get_rect(25, 100), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.y_end, "Y2", get_rect(150, 100), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;

	set_text(&al->text.cancel, "CANCEL", get_rect(600, 20), add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);
	init_player(al, &al->play);
	creat_entity(al);
	init_trigo(al);
	init_status(al);
	al->status = GAME;
	al->status = EDIT;
	al->fps = 60;
	al->g = DEFAULT_G;
	al->fov = DEFAULT_FOV;
	al->stretch = WIN_SIZEY + HORIZON_LIMIT * 2;
	al->nb_texgp = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->sdlwin = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
			WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->sdlsurf = SDL_GetWindowSurface(al->sdlwin)))
		yeet(al);
	al->pix = al->sdlsurf->pixels;
	init_ttf(al);
	if (al->status == EDIT)
		init_edit(al);
	get_map(al);
	// printf("222\n");
	// init_texgrp(al);
	init_ttf(al);
	ft_bzero(&al->k, sizeof(t_keys));
	al->edit.stat = FIRST_CLICK;
	al->edit.zoom = 15;
	// al->nb_sect = 0;
}
