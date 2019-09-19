/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/19 21:07:15 by becaraya         ###   ########.fr       */
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
	if (!(al->wall = (t_wall *)ft_memalloc(sizeof(t_wall))))
		yeet(al);
	al->wall->next = NULL;
	al->wall->prev = NULL;
}

static void		init_edit(t_al *al)
{		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);
	if (!(al->win_ = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY, WIN_SIZEX,
				WIN_SIZEY, SDL_WINDOW_RESIZABLE)))
		yeet(al);
	if ((al->ren_ = SDL_CreateRenderer(al->win_, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC)) == NULL)
		yeet(al);
	if ((al->tex_ = SDL_CreateTexture(al->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC, WIN_SIZEX, WIN_SIZEY)) == NULL)
		yeet(al);
	if ((al->pix_ = ft_memalloc(WIN_SIZEX * WIN_SIZEY * sizeof(int))) == NULL)
		yeet(al);
}

void	init(t_al *al)
{
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
	// init_edit(al);
	init_text(al);
	init_wall(al);
	ft_bzero(al, sizeof(t_al *));
	ft_bzero(&al->k, sizeof(t_keys));
	al->wall->x1 = -1;
	al->wall->x2 = -1;
	al->wall->y1 = -1;
	al->wall->y2 = -1;
	al->status = ST_EDIT;
	al->fps = 60;
	// al->edit.stat = FIRST_CLICK;
	al->edit.stat = RECTANGLE_SELECT;
	al->edit.zoom = 15;
	al->c_wall = 0;
}
