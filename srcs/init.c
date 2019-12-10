/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:19:03 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/10 18:53:09 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <float.h>

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
	al->nb_ent = 1;
	al->ent = ft_memalloc(al->nb_ent * sizeof(t_mob));
	al->rotent = ft_memalloc(al->nb_ent * sizeof(t_mob));
	al->ent[0].csec = 1;
	al->ent[0].posx = 4;
    al->ent[0].posy = 4;
	al->ent[0].posz = al->sec[al->ent[0].csec].fl_hei;
	al->ent[0].velx = 0;
	al->ent[0].gd_vel = 0;
	al->ent[0].on_ground = 1;
	al->ent[0].alive = 1;
	al->ent[0].dir = 0;

	al->ent[0].size = 2;
	al->ent[0].width = 1.7;
	al->ent[0].mass = 50;
	al->ent[0].power = 200;
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

// jvous en prie utilisez pas ça c'est de la merde
void			load_imgs(t_tex_group *tgp, t_tex_or *or, char *str)
{
	unsigned char	*tmp;
	unsigned char	buf[1000];
	size_t			size;
	int				fd;

	size = tgp->size_x * tgp->size_y * sizeof(unsigned *);
	tmp = malloc(tgp->size_x * tgp->size_y * 3);
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
}

/*
** m'en bat les couilles il s'apelle le goret si vs voulez vous battre jvous
** attend gare du nord
*/

void			load_goret(t_al *al)
{
	al->nb_texgp = 1;
	al->texgp = malloc(al->nb_texgp * sizeof(t_tex_group));
	al->texgp[0].nb_tex = 4;
	al->texgp[0].size_x = 512;
	al->texgp[0].size_y = 512;
	load_imgs(al->texgp, al->texgp->or + 0, "ressources/sprite/or1");
	load_imgs(al->texgp, al->texgp->or + 1, "ressources/sprite/or2");
	load_imgs(al->texgp, al->texgp->or + 2, "ressources/sprite/or3");
	load_imgs(al->texgp, al->texgp->or + 3, "ressources/sprite/or4");
	load_imgs(al->texgp, al->texgp->or + 4, "ressources/sprite/or5");
	load_imgs(al->texgp, al->texgp->or + 5, "ressources/sprite/or6");
	load_imgs(al->texgp, al->texgp->or + 6, "ressources/sprite/or7");
	load_imgs(al->texgp, al->texgp->or + 7, "ressources/sprite/or8");
	printf("Goret loaded\n");
}

void			init(t_al *al, char *str)
{
	if (hms_parser(al, str))
		exit(0);

	load_goret(al);
	//bmp_to_tex(al->tex + 3, "ressources/menu_3.bmp", 1280, 720);
	// T H E  O P E N A T O R, can open a path through every walls, even through you're mom
	//for (int x = 1; x <= al->nb_sec; x++)
	//	for (int z = 0; z < al->sec[x].nb_wal; z++)
	//		al->sec[x].walls[z].sec_lnk ? al->sec[x].walls[z].is_cross = 1 : 0;


/*	al->nb_tex = 3;
	al->tex = ft_memalloc((al->nb_tex + 1) * sizeof(t_tex));
	bmp_to_tex(al->tex + 0, "ressources/wall_tex.bmp", 800, 600);
	bmp_to_tex(al->tex + 1, "ressources/Untitled-1.bmp", 800, 800);
	bmp_to_tex(al->tex + 2, "ressources/floor_tex.bmp", 950, 950);
	bmp_to_tex(al->tex + 3, "ressources/ceiling_tex.bmp", 512, 512);
	al->tex[4].size_x = 1;
	al->tex[4].size_y = 1;
	al->tex[4].pix = ft_memalloc(sizeof(unsigned));

	t_walls *w;
	t_sector *s;
	al->play.posx = 1;
	al->play.posy = 1;
	al->play.csec = 1;
	al->nb_sec = 5; //////////////////////////////////////////////////////////////////////////////////////////////////////////////
	al->sec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector));
	al->rotsec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector));

	//sec 1
	s = al->sec + 1;
	s->fl_hei = 0;
	s->ce_hei = 6;
	s->fl_tex = 2;
	s->ce_tex = 3;
	s->nb_wal = 16; // << check this
	s->walls = ft_memalloc(al->sec[1].nb_wal * sizeof(t_walls));
	al->rotsec[1].walls = ft_memalloc(al->sec[1].nb_wal * sizeof(t_walls));
	// CHECK  ^^^ THIS
	w = s->walls; // 0
	w->sec_lnk = 2;
	w->bot_tex = 1;
	w->x1 = 1000 / 100.0; // 1000,1000
	w->y1 = 1000 / 100.0;
	w->x2 = 1400 / 100.0; // 1400,1000
	w->y2 = 1000 / 100.0;
	w++; // 1
	w->sec_lnk = 2;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1400 / 100.0; // 1400,1500
	w->y2 = 1500 / 100.0;
	w++; // 2
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 2000 / 100.0; // 2000,1500
	w->y2 = 1500 / 100.0;
	w++; // 3;
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 2000 / 100.0; // 2000,0
	w->y2 = 0 / 100.0;
	w++; // 4;
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 0 / 100.0; // 0,0
	w->y2 = 0 / 100.0;
	w++; // 5;
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 0 / 100.0; // 0,1500
	w->y2 = 1500 / 100.0;
	w++; // 6;
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 400 / 100.0; // 400,1500
	w->y2 = 1500 / 100.0;
	w++; // 7;
	w->sec_lnk = 2;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 400 / 100.0; // 400,1000
	w->y2 = 1000 / 100.0;
	w++; // 8;
	w->sec_lnk = 2;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 700,1000
	w->y2 = 1000 / 100.0;
	w++; // 9;
	w->sec_lnk = 3;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 700,975
	w->y2 = 975 / 100.0;

	w++; // 10;
	w->sec_lnk = 4;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 800,950
	w->y2 = 950 / 100.0;

	w++; // 11;
	w->sec_lnk = 5;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 800,925
	w->y2 = 925 / 100.0;
	w++; // 12;
	w->sec_lnk = 5;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,925
	w->y2 = 925 / 100.0;
	w++; // 13;
	w->sec_lnk = 5;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,950
	w->y2 = 950 / 100.0;

	w++; // 14;
	w->sec_lnk = 4;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,975
	w->y2 = 975 / 100.0;
	w++; // 15;
	w->sec_lnk = 3;
	w->bot_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = s->walls->x1; // origin
	w->y2 = s->walls->y1;

	// sec 2
	s++;
	s->fl_hei = 4;
	s->ce_hei = 6;
	s->fl_tex = 2;
	s->ce_tex = 3;
	s->nb_wal = 6; // rember this
	s->walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	al->rotsec[2].walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	// CHECK  ^^^ THIS
	w = s->walls; // 0
	w->sec_lnk = 1;
	w->x1 = 400 / 100.0; // 400,1000
	w->y1 = 1000 / 100.0;
	w->x2 = 800 / 100.0; // 800,1000
	w->y2 = 1000 / 100.0;
	w++; // 1
	w->sec_lnk = 3;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,1000
	w->y2 = 1000 / 100.0;
	w++; // 2
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1400 / 100.0; // 1400,1000
	w->y2 = 1000 / 100.0;
	w++; // 3
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1400 / 100.0; // 1400,1500
	w->y2 = 1500 / 100.0;
	w++; // 4
	w->wall_tex = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 400 / 100.0; // 400,1500
	w->y2 = 1500 / 100.0;
	w++; // 5
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = s->walls->x1; // origin
	w->y2 = s->walls->y1;

	// sec 3
	s++;
	s->fl_hei = 0.75;
	s->ce_hei = 6;
	s->fl_tex = 2;
	s->ce_tex = 3;
	s->nb_wal = 4; // rember this
	s->walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	al->rotsec[3].walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	// CHECK  ^^^ THIS
	w = s->walls; // 0
	w->sec_lnk = 2;
	w->bot_tex = 1;
	w->x1 = 800 / 100.0; // 700,1000
	w->y1 = 1000 / 100.0;
	w->x2 = 1000 / 100.0; // 1000,1000
	w->y2 = 1000 / 100.0;
	w++; // 1
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,975
	w->y2 = 975 / 100.0;
	w++; // 2
	w->sec_lnk = 4;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 800,975
	w->y2 = 975 / 100.0;
	w++; // 3
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = s->walls->x1; // origin
	w->y2 = s->walls->y1;

	// sec 4
	s++;
	s->fl_hei = 0.5;
	s->ce_hei = 6;
	s->fl_tex = 2;
	s->ce_tex = 3;
	s->nb_wal = 4; // rember this
	s->walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	al->rotsec[4].walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	// CHECK  ^^^ THIS
	w = s->walls; // 0
	w->sec_lnk = 3;
	w->bot_tex = 1;
	w->x1 = 800 / 100.0; // 800,975
	w->y1 = 975 / 100.0;
	w->x2 = 1000 / 100.0; // 1000,975
	w->y2 = 975 / 100.0;
	w++; // 1
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,950
	w->y2 = 950 / 100.0;
	w++; // 2
	w->sec_lnk = 5;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 800,950
	w->y2 = 950 / 100.0;
	w++; // 3
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = s->walls->x1; // origin
	w->y2 = s->walls->y1;

	// sec 5
	s++;
	s->fl_hei = 0.25;
	s->ce_hei = 6;
	s->fl_tex = 2;
	s->ce_tex = 3;
	s->nb_wal = 4; // rember this
	s->walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	al->rotsec[5].walls = ft_memalloc(s->nb_wal * sizeof(t_walls));
	// CHECK  ^^^ THIS
	w = s->walls; // 0
	w->sec_lnk = 4;
	w->bot_tex = 1;
	w->x1 = 800 / 100.0; // 800,950
	w->y1 = 950 / 100.0;
	w->x2 = 1000 / 100.0; // 1000,950
	w->y2 = 950 / 100.0;
	w++; // 1
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 1000 / 100.0; // 1000,925
	w->y2 = 925 / 100.0;
	w++; // 2
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = 800 / 100.0; // 800,925
	w->y2 = 925 / 100.0;
	w++; // 3
	w->sec_lnk = 1;
	w->x1 = (w - 1)->x2;
	w->y1 = (w - 1)->y2;
	w->x2 = s->walls->x1; // origin
	w->y2 = s->walls->y1;*/

	init_player(al, &al->play);
	creat_entity(al);
	init_trigo(al);
	init_status(al);
	al->status = EDIT;
	al->status = GAME;
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
		init_edit(al);

	// get_map(al);
	// get_sec_tab(al);
	// get_map(al);

	//init_ttf(al);
	ft_bzero(&al->k, sizeof(t_keys));
	al->edit.stat = FIRST_CLICK;
	al->edit.zoom = 15;
}
