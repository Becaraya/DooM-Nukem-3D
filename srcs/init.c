/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/30 15:07:29 by pitriche         ###   ########.fr       */
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
	pl->dir = 0;
	pl->horizon = 0;
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

static void		init_trigo(t_al *al)
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

void			load_hud(t_al *al)
{
	bmp_to_tex(&(al->h), "ressources/HUD/heart.bmp", 46, 41);
	bmp_to_tex(&(al->weapon[0]), "ressources/weapon/shotgun1.bmp", 102, 85);
	bmp_to_tex(&(al->weapon[1]), "ressources/weapon/shotgun_fire.bmp", 102, 105);
	bmp_to_tex(&(al->weapon[2]), "ressources/weapon/shotgun_fire2.bmp", 118, 150);
	bmp_to_tex(&(al->weapon[3]), "ressources/weapon/shotgun2.bmp", 118, 131);
	bmp_to_tex(&(al->weapon[4]), "ressources/weapon/shotgun3.bmp", 160, 140);
	bmp_to_tex(&(al->weapon[5]), "ressources/weapon/shotgun4.bmp", 160, 176);
	bmp_to_tex(&(al->weapon[6]), "ressources/weapon/shotgun5.bmp", 133, 172);
	al->f = al->weapon[0];
}

static void		init_anims(t_al *al)
{
	unsigned		i;

	al->fire_anim = 420000000;
	i = 0;
	while (i < al->nb_ent)
		al->ent[i++].anim = 42000000;
}

/*
** not so horrible function to add correct transparency to all death animation
** frames
*/

static void		im_not_going_to_hell_for_this(t_al *al, int ipix)
{
	int				i;

	i = 0;
	while (i < 8)
	{
		if (al->mob_death[i].pix[ipix] != 0xffff)
			al->mob_death[i].pix[ipix] |= 0xff000000;
		i++;
	}
}

void			load_death(t_al *al)
{
	unsigned		i;

	bmp_to_tex(&al->you_died, "ressources/you_died.bmp", 518, 93);
	bmp_to_tex(al->mob_death + 0, "ressources/mob_death/0.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 1, "ressources/mob_death/1.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 2, "ressources/mob_death/2.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 3, "ressources/mob_death/3.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 4, "ressources/mob_death/4.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 5, "ressources/mob_death/5.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 6, "ressources/mob_death/6.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 7, "ressources/mob_death/7.bmp", 512, 512);
	i = 0;
	if (al->mob_death[0].size_x == 512 && al->mob_death[1].size_x == 512 &&
		al->mob_death[2].size_x == 512 && al->mob_death[3].size_x == 512 &&
		al->mob_death[4].size_x == 512 && al->mob_death[5].size_x == 512 &&
		al->mob_death[6].size_x == 512 && al->mob_death[7].size_x == 512)
		while (i < 262144)
		{
			im_not_going_to_hell_for_this(al, i);
			i++;
		}
}

void			load_goret(t_tex_group *tgp)
{
	unsigned	or;
	unsigned	i;
	unsigned	*tmp;
	char		str[28];

	tgp->nb_tex = 4;
	tgp->size_x = 512;
	tgp->size_y = 512;
	or = 0;
	ft_strcpy(str, "ressources/sprite/or1/1.bmp");
	while (or < 8)
	{
		if (!(tgp->or[or].pix = ft_memalloc(tgp->nb_tex * sizeof(unsigned *))))
			exit(pr_err(MERROR_MESS));
		str[20] = or + '1';
		i = 0;
		while (i < tgp->nb_tex)
		{
			str[22] = i + '1';
			bmp_to_pix(tgp->or[or].pix + i, str, 512, 512);
			tmp = tgp->or[or].pix[i];
			if (tmp[0] == 0xffff00ff && tmp[1] == 0xff000000 && tmp[2] ==
				0xff000000 && tmp[3] == 0xffff00ff)
			{
				tgp->size_x = 2;
				tgp->size_y = 2;
				ft_putchar('X');
			}
			else
				ft_putchar('O');
			i++;
		}
		or++;
	}
}

void			init_textures(t_al *al)
{
	load_hud(al);
	load_death(al);
	if (!al->tex)
	{
		al->nb_tex = 3;
		if (!(al->tex = ft_memalloc((al->nb_tex + 1) * sizeof(t_tex))))
			exit(0);
		bmp_to_tex(al->tex + 0, "ressources/skybox.bmp", 800, 600);
		bmp_to_tex(al->tex + 1, "ressources/wall_tex.bmp", 800, 800);
		bmp_to_tex(al->tex + 2, "ressources/floor_tex.bmp", 950, 950);
		bmp_to_tex(al->tex + 3, "ressources/ceiling_tex.bmp", 512, 512);
	}
	if (!al->texgp)
	{
		al->nb_texgp = 1;
		if (!(al->texgp = ft_memalloc(al->nb_texgp * sizeof(t_tex_group))))
			exit(0);
		ft_putstr("Load ressource textures:\nv________________________________v"
			"\n[");
		load_goret(al->texgp);
		ft_putstr("] done !\n");
	}
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
