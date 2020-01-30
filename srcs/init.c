/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/30 11:15:00 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** je sait pas ou ranger cette fonction
*/

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
