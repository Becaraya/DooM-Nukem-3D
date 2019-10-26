/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/25 12:01:19 by becaraya         ###   ########.fr       */
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
	pl->eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
	pl->on_ground = 1;
	pl->alive = 0;
	pl->posz = al->sec[pl->csec].fl_hei;
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

SDL_Color		add_color(int r, int g, int b, int a)
{
	SDL_Color c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

void			init_ttf(t_al *al)
{
	al->ttf_st = (!TTF_Init()) ? 1 : 0; 
	if (!(al->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		yeet(al);

	al->color = add_color(255,255,255, 0);
	
}

static void		init_edit(t_al *al)
{
	if (!(al->win_ed = SDL_CreateWindow(WIN_TITLE, WIN_POSX + WIN_SIZEX,
		WIN_POSY, WIN_EDIT_SIZEX, WIN_EDIT_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->surf_ed = SDL_GetWindowSurface(al->win_ed)))
		yeet(al);
	al->pix_ed = al->sdlsurf->pixels;
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);
	//free(al->tex[0].pix);
	//bmp_to_tex(al->tex + 0, "ressources/white-brick-texture.bmp", 800, 600);
	//free(al->tex[1].pix);
	//bmp_to_tex(al->tex + 1, "ressources/wall_tex.bmp", 800, 600);
	//free(al->tex[2].pix);
	//bmp_to_tex(al->tex + 2, "ressources/floor_tex.bmp", 950, 950);
	//free(al->tex[3].pix);
	//bmp_to_tex(al->tex + 3, "ressources/ceiling_tex.bmp", 512, 512);
	/*al->sec[2].fl_tex = 2;
	al->sec[2].ce_tex = 3;
	al->sec[1].walls[0].bot_tex = 1;
	al->sec[1].walls[0].top_tex = 1;
	al->sec[1].walls[1].wall_tex = 1;
	al->sec[1].walls[4].wall_tex = 1;*/
	
	
	init_player(al, &al->play);
	init_trigo(al);
	init_status(al);
	al->status = GAME;
	//al->status = EDIT;
	al->fps = 60;
	al->g = DEFAULT_G;
	al->fov = DEFAULT_FOV;
	al->stretch = WIN_SIZEY + HORIZON_LIMIT * 2;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->sdlwin = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
			WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->sdlsurf = SDL_GetWindowSurface(al->sdlwin)))
		yeet(al);
	al->pix = al->sdlsurf->pixels;
	init_wall(al);
	if (al->status == EDIT)
		init_edit(al);
	init_ttf(al);
	ft_bzero(&al->k, sizeof(t_keys));
	al->edit.stat = FIRST_CLICK;
	// al->edit.stat = RECTANGLE_SELECT;
	al->edit.zoom = 15;
	al->c_wall = 0; // bzero init everything to 0, this func is for !0 inits ;)
}
