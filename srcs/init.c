/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/29 15:03:05 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** je sait pas ou ranger cette fonction
*/

void			creat_entity(t_al *al)
{/*
	unsigned int	i;

	al->nb_ent = 2;
	if (!(al->ent = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	if (!(al->rotent = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	i = -1;
	while (++i < al->nb_ent)
	{
		al->ent[i].csec = 1;
		al->ent[i].posx = 12;
		al->ent[i].posy = 4 + (double)i * 5;
		al->sec ? al->ent[i].posz = al->sec[al->ent[0].csec].fl_hei : 0;
		al->ent[i].velx = 0;
		al->ent[i].vely = 0;
		al->ent[i].velz = 0;
		al->ent[i].gd_vel = 0;
		al->ent[i].on_ground = 1;
		al->ent[i].alive = 10;
		al->ent[i].dir = 0;
		al->ent[i].size = 2.5;
		al->ent[i].width = 2.3;
		al->ent[i].mass = 50;
		al->ent[i].power = 200;
		al->ent[i].hit = 1;
		al->ent[i].index = i;
		al->ent[i].fly = 1;
	}*/
	return ;
}

static void		init_anims(t_al *al)
{
	unsigned		i;

	al->fire_anim = 420000000;
	i = 0;
	while (i < al->nb_ent)
		al->ent[i++].anim = 42000000;
}

static void		init_two(t_al *al, char *str)
{
	if (!(al->sdlsurf = SDL_GetWindowSurface(al->sdlwin)))
		yeet(al);
	al->pix = al->sdlsurf->pixels;
	init_ttf(al);
	al->tex_choice = 0;
	if (al->status == EDIT)
	{
		init_edit(al);
		str ? get_map(al) : 0;
	}
	if (al->status == GAME)
	{
		set_text(&al->text.t, "TEXT", get_rect(300, 330),
		add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	}
	al->hard = 2;
	ft_bzero(&al->k, sizeof(t_keys));
	init_anims(al);
	al->edit.stat = SELECT;
	al->edit.sect_end = -1;
	al->edit.zoom = 10;
	al->edit.index_sect = al->nb_sec;
	(al->sect) ? al->edit.index_wall = al->sect->nb_wal - 1 : 0;
}

void			init(t_al *al, char *str, int ed)
{
	if (str)
		if (hms_parser(al, str))
			exit(0);
	init_textures(al);
	init_player(al, &al->play);
	creat_entity(al);
	init_trigo(al);
	init_status(al);
	al->fps = 60;
	al->status = ed ? EDIT : GAME;
	al->status = EDIT;
	al->g = DEFAULT_G;
	al->fov = DEFAULT_FOV;
	al->stretch = WIN_SIZEY + HORIZON_LIMIT * 2;
	al->nb_texgp = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->sdlwin = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
			WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	init_two(al, str);
}
