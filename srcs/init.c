/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/23 15:11:20 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		init_status(t_al *al)
{
	al->stat_fnc[MENU] = menu;
	al->stat_fnc[GAME] = game;
	al->stat_fnc[DEAD] = dead;
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
	pl->alive = 50;
	pl->posz = al->sec[pl->csec].fl_hei;
}

/*
** je sait pas ou ranger cette fonction
*/

void			creat_entity(t_al *al)
{
	int i;

	al->nb_ent = 1;
	if (!(al->ent = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	if (!(al->rotent = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	i = -1;
	while (++i < al->nb_ent)
	{
		al->ent[i].csec = 1;
		al->ent[i].posx = 12;
		al->ent[i].posy = 4 + (double)i;
		al->ent[i].posz = al->sec[al->ent[0].csec].fl_hei;
		al->ent[i].velx = 0;
		al->ent[i].gd_vel = 0;
		al->ent[i].on_ground = 1;
		al->ent[i].alive = 1;
		al->ent[i].dir = 0;
		al->ent[i].size = 2.5;
		al->ent[i].width = 2.3;
		al->ent[i].mass = 50;
		al->ent[i].power = 200;
		al->ent[i].hit = 1;
	}
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
}

static void		init_edit(t_al *al)
{
	if (!(al->win_ed = SDL_CreateWindow(WIN_TITLE, WIN_POSX + WIN_SIZEX,
		WIN_POSY, WIN_EDIT_SIZEX, WIN_EDIT_SIZEY, SDL_WINDOW_SHOWN)))
		yeet(al);
	if (!(al->surf_ed = SDL_GetWindowSurface(al->win_ed)))
		yeet(al);
	al->pix_ed = al->surf_ed->pixels;
	init_text_edit(al);
}

/*
void			load_imgs(t_tex_group *tgp, t_tex_or *or, char *str)
{
	unsigned char	*tmp;
	unsigned char	buf[1000];
	size_t			size;
	int				fd;

	size = tgp->size_x * tgp->size_y * sizeof(unsigned *);
	tmp =  malloc(tgp->size_x * tgp->size_y * 3);
	or->pix = malloc(tgp->nb_tex * sizeof(unsigned **));

	ft_strcpy((char *)tmp, str);
	fd = open(ft_strcat((char *)tmp, "/1.bmp"), O_RDONLY);
	read(fd, buf, 14);
	read(fd, buf, *(unsigned *)(buf + 10) - 14);
	or->pix[0] = malloc(size);
	read(fd, tmp, tgp->size_x * tgp->size_y * 3);
	for (unsigned i = 0; i < tgp->size_x * tgp->size_y; i++)
		or->pix[0][tgp->size_x * tgp->size_y - i] = tmp[i * 3 + 2] * 0x10000 +
			tmp[i * 3 + 1] * 0x100 +tmp[i * 3];

	ft_strcpy((char *)tmp, str);
	fd = open(ft_strcat((char *)tmp, "/2.bmp"), O_RDONLY);
	read(fd, buf, 14);
	read(fd, buf, *(unsigned *)(buf + 10) - 14);
	or->pix[1] = malloc(size);
	read(fd, tmp, tgp->size_x * tgp->size_y * 3);
	for (unsigned i = 0; i < tgp->size_x * tgp->size_y; i++)
		or->pix[1][tgp->size_x * tgp->size_y - i] = tmp[i * 3 + 2] * 0x10000 +
			tmp[i * 3 + 1] * 0x100 +tmp[i * 3];

	ft_strcpy((char *)tmp, str);
	fd = open(ft_strcat((char *)tmp, "/3.bmp"), O_RDONLY);
	read(fd, buf, 14);
	read(fd, buf, *(unsigned *)(buf + 10) - 14);
	or->pix[2] = malloc(size);
	read(fd, tmp, tgp->size_x * tgp->size_y * 3);
	for (unsigned i = 0; i < tgp->size_x * tgp->size_y; i++)
		or->pix[2][tgp->size_x * tgp->size_y - i] = tmp[i * 3 + 2] * 0x10000 +
			tmp[i * 3 + 1] * 0x100 +tmp[i * 3];

	ft_strcpy((char *)tmp, str);
	fd = open(ft_strcat((char *)tmp, "/4.bmp"), O_RDONLY);
	read(fd, buf, 14);
	read(fd, buf, *(unsigned *)(buf + 10) - 14);
	or->pix[3] = malloc(size);
	read(fd, tmp, tgp->size_x * tgp->size_y * 3);
	for (unsigned i = 0; i < tgp->size_x * tgp->size_y; i++)
		or->pix[3][tgp->size_x * tgp->size_y - i] = tmp[i * 3 + 2] * 0x10000 +
			tmp[i * 3 + 1] * 0x100 +tmp[i * 3];


	for (unsigned i = 0; i < tgp->size_x * tgp->size_y; i++)
	{
		//printf("%#x \n", or->pix[0][i]);
		//or->pix[0][i] == 0xffff0000 ? or->pix[0][i] = 0 : 0;
		//da = (or->pix[0][i] >> 24) & 0xff;
		or->pix[0][i] != 0xffff ? or->pix[0][i] += 0x1000000 : 0;
		or->pix[1][i] != 0xffff ? or->pix[1][i] += 0x1000000 : 0;
		or->pix[2][i] != 0xffff ? or->pix[2][i] += 0x1000000 : 0;
		or->pix[3][i] != 0xffff ? or->pix[3][i] += 0x1000000 : 0;
	}
	free(tmp);
}*/

void			load_hud(t_al *al)
{
	bmp_to_tex(&(al->h), "ressources/HUD/heart.bmp", 46, 41);
	bmp_to_tex(&(al->f), "ressources/HUD/chop.bmp", 100, 133);
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);
	load_hud(al);
	init_player(al, &al->play);
	creat_entity(al);
	init_trigo(al);
	init_status(al);
	bmp_to_tex(&al->you_died, "ressources/you_died.bmp", 518, 93);
	al->status = EDIT;
	//al->status = GAME;
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
	al->tex_choice = 0;
	if (al->status == EDIT)
	{
		init_edit(al);
		get_map(al);
	}
	// get_sec_tab(al);
	// get_map(al);
	al->fire_anim = 420000000;
	ft_bzero(&al->k, sizeof(t_keys));
	al->edit.stat = SELECT;
	al->edit.zoom = 10;
	al->edit.index_sect = al->nb_sec;
	(al->sect) ? al->edit.index_wall = al->sect->nb_wal - 1 : 0;
}
