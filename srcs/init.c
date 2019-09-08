/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/08 17:04:49 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		init_text(t_al *al)
{
	t_texture	txt;

	txt = al->txt;
	// txt.s_menu = parse_tex(al, "ressources/menu.bmp", 1280, 720);
	// txt.ic.chest = parse_tex(al, "ressources/icon/chest.bmp", 699, 604);
	// txt.ic.click = parse_tex(al, "ressources/icon/click.bmp", 700, 605);
	// txt.ic.path = parse_tex(al, "ressources/icon/path.bmp", 700, 601);
	// txt.ic.portal = parse_tex(al, "ressources/icon/portal.bmp", 699, 612);
	// txt.ic.wall = parse_tex(al, "ressources/icon/wall.bmp", 700, 609);
}

static void		init_wall(t_al *al)
{
	if (!(al->wall = (t_wall *)malloc(sizeof(t_wall))))
		yeet(al);
	al->wall->next = NULL;
	al->wall->prev = NULL;
}

void	init(t_al *al)
{
	al->status = ST_EDIT;
	al->fps = 60;
	al->edit.stat = T_WALL_1;
	al->c_wall = 0;
	al->edit.zoom = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->win = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY, WIN_SIZEX,
				WIN_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if ((al->ren = SDL_CreateRenderer(al->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC)) == NULL)
		yeet(al);
	if ((al->tex = SDL_CreateTexture(al->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC, WIN_SIZEX, WIN_SIZEY)) == NULL)
		yeet(al);
	if ((al->pix = ft_memalloc(WIN_SIZEX * WIN_SIZEY * sizeof(int))) == NULL)
		yeet(al);
	init_text(al);
	init_wall(al);
}
