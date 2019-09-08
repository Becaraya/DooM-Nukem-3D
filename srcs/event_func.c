/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 09:18:54 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/08 18:01:55 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	keyup_func(t_al *al, SDL_KeyboardEvent kev)
{
	kev.keysym.sym == SDLK_w ? al->k.w = 0 : 0;
	kev.keysym.sym == SDLK_a ? al->k.a = 0 : 0;
	kev.keysym.sym == SDLK_s ? al->k.s = 0 : 0;
	kev.keysym.sym == SDLK_d ? al->k.d = 0 : 0;
	kev.keysym.sym == SDLK_LEFT ? al->k.left = 0 : 0;
	kev.keysym.sym == SDLK_RIGHT ? al->k.righ = 0 : 0;
	kev.keysym.sym == SDLK_LSHIFT ? al->k.lshift = 0 : 0;
	kev.keysym.sym == SDLK_SPACE ? al->k.space = 0 : 0;
	kev.keysym.sym == SDLK_UP ? al->k.up = 0 : 0;
	kev.keysym.sym == SDLK_DOWN ? al->k.down = 0 : 0;
	kev.keysym.sym == SDLK_LCTRL ? al->k.ctrl = 0 : 0;
}

void		key_func(t_al *al)
{
	SDL_KeyboardEvent kev;

	kev = al->ev.key;
	if (al->ev.type == SDL_KEYDOWN)
	{
		kev.keysym.sym == SDLK_ESCAPE ? yeet(al) : 0;
		if (kev.keysym.sym == SDLK_F1)
			al->status = (al->status == ST_GAME) ? ST_PAUSE : ST_GAME;
		kev.keysym.sym == SDLK_w ? al->k.w = 1 : 0;
		kev.keysym.sym == SDLK_a ? al->k.a = 1 : 0;
		kev.keysym.sym == SDLK_s ? al->k.s = 1 : 0;
		kev.keysym.sym == SDLK_d ? al->k.d = 1 : 0;
		kev.keysym.sym == SDLK_LEFT ? al->k.left = 1 : 0;
		kev.keysym.sym == SDLK_RIGHT ? al->k.righ = 1 : 0;
		kev.keysym.sym == SDLK_UP ? al->k.up = 1 : 0;
		kev.keysym.sym == SDLK_DOWN ? al->k.down = 1 : 0;
		kev.keysym.sym == SDLK_LSHIFT ? al->k.lshift = 1 : 0;
		kev.keysym.sym == SDLK_SPACE ? al->k.space = 1 : 0;
		kev.keysym.sym == SDLK_LCTRL ? al->k.ctrl = 1 : 0;
	}
	else
		keyup_func(al, kev);
}

void		mouse_menu(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.clicks == 1)
	{
		if (bev.button == SDL_BUTTON_LEFT)
		{
			//printf("CLICK y =%d = =%d\n", bev.y, bev.x);
			if (bev.y > 228 && bev.y < 315 && bev.x > 766 && bev.x < 940)
				printf("GO\n");
			if (bev.y > 472 && bev.y < 574 && bev.x > 772 && bev.x < 943)
				printf("QUIT\n");
			//	yeet(al);
			if (bev.y > 347 && bev.y < 444 && bev.x > 720 && bev.x < 1004)
				printf("SETTING\n");
		}
	}
}

void		new_wall(t_al *al)
{
	t_wall	*new;

	if (!(new = (t_wall *)malloc(sizeof(t_wall))))
		yeet(al);
	new->x1 = al->wall->x2;
	new->y1 = al->wall->y2;
	new->x2 = new->x1;
	new->y2 = new->y1;

	new->prev = al->wall;
	new->next = NULL;
	if (al->wall->next)
		al->wall->next = new;
	al->wall = new;
	
}

void		mouse_edit(t_al *al)
{	
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (al->edit.stat == T_WALL_1)
	{
		if (bev.clicks == 1)
		{
			al->wall->x1 = bev.x;
			al->wall->y1 = bev.y;
			al->wall->x2 = bev.x;
			al->wall->y2 = bev.y;
			printf("WALL 1 = %d\n", al->wall->x1);
			al->edit.stat = T_WALL_2;
			al->c_wall = al->c_wall + 1;
		}
	}
	else if (al->edit.stat == T_WALL_2)
	{
		if (bev.clicks == 1)
		{
			al->edit.stat = T_WALL_1;
			printf("Wall e\n");
			new_wall(al);
			printf("WALL 3\n");
		}
	}
}


void		mouse_press(t_al *al)
{
	if (al->status == ST_MENU)
		mouse_menu(al);
	else if (al->status == ST_EDIT)
		mouse_edit(al);
}
/*
if (al->status == ST_GAME)
{
	if ((mev.xrel < 0 && mev.x < WIN_SIZEX / 2)
		|| (mev.xrel > 0 && mev.x > WIN_SIZEX / 2))
		printf("peux etre la droite ou la gauche\n");
	if (mev.yrel < 0 && mev.y < WIN_SIZEY / 2)
		printf("et ca c est peux etre le haut\n");
	if (mev.yrel > 0 && mev.y > WIN_SIZEY / 2)
		printf("ou ca c est le haut...\n");
}
*/
void		mouse_func(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (al->edit.stat == T_WALL_2)
	{
		al->wall->x2 = mev.x;
		al->wall->y2 = mev.y;
	}
}
