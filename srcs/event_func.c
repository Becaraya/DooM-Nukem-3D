/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 09:18:54 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/29 12:07:14 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	z_func(t_al *al)
{
	if (al->ev.type == SDL_KEYDOWN)
	{
		al->play.size = PLAYER_CROUCH;
		al->play.eyez -= PLAYER_SIZE - PLAYER_CROUCH;
		al->play.power_mult = 0.3;
	}
	else
	{
		al->play.size = PLAYER_SIZE;
		al->play.eyez += PLAYER_SIZE - PLAYER_CROUCH;
		al->play.power_mult = 1;
	}
}

static void	keyup_func(t_al *al, SDL_KeyboardEvent kev)
{
	kev.keysym.sym == SDLK_w ? al->k.w = 0 : 0;
	kev.keysym.sym == SDLK_a ? al->k.a = 0 : 0;
	kev.keysym.sym == SDLK_s ? al->k.s = 0 : 0;
	kev.keysym.sym == SDLK_d ? al->k.d = 0 : 0;
	kev.keysym.sym == SDLK_LEFT ? al->k.left = 0 : 0;
	kev.keysym.sym == SDLK_RIGHT ? al->k.righ = 0 : 0;
	kev.keysym.sym == SDLK_LSHIFT ? al->play.power = PLAYER_AERO_POWER : 0;
	kev.keysym.sym == SDLK_UP ? al->k.up = 0 : 0;
	kev.keysym.sym == SDLK_DOWN ? al->k.down = 0 : 0;
	kev.keysym.sym == SDLK_SPACE ? al->k.space = 0 : 0;
}

void		key_func(t_al *al)
{
	SDL_KeyboardEvent kev;

	kev = al->ev.key;
	kev.keysym.sym == SDLK_z ? z_func(al) : 0;
	if (al->ev.type == SDL_KEYDOWN)
	{
		kev.keysym.sym == SDLK_ESCAPE ? yeet(al) : 0;
		if (kev.keysym.sym == SDLK_F1)
			al->status = (al->status == GAME) ? PAUSE : GAME;
		kev.keysym.sym == SDLK_w ? al->k.w = 1 : 0;
		kev.keysym.sym == SDLK_a ? al->k.a = 1 : 0;
		kev.keysym.sym == SDLK_s ? al->k.s = 1 : 0;
		kev.keysym.sym == SDLK_d ? al->k.d = 1 : 0;
		kev.keysym.sym == SDLK_LEFT ? al->k.left = 1 : 0;
		kev.keysym.sym == SDLK_RIGHT ? al->k.righ = 1 : 0;
		kev.keysym.sym == SDLK_UP ? al->k.up = 1 : 0;
		kev.keysym.sym == SDLK_DOWN ? al->k.down = 1 : 0;
		kev.keysym.sym == SDLK_LSHIFT ? al->play.power = PLAYER_ANA_POWER : 0;
		kev.keysym.sym == SDLK_SPACE ? al->k.space = 1 : 0;
		kev.keysym.sym == SDLK_KP_MINUS ? al->fov *= 1.1 : 0;
		kev.keysym.sym == SDLK_KP_PLUS ? al->fov /= 1.1 : 0;
	}
	else
		keyup_func(al, kev);
}

void		mouse_press_menu(t_al *al)
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
			if (bev.y > 347 && bev.y < 444 && bev.x > 720 && bev.x < 1004)
				printf("SETTING\n");
		}
	}
}

void		mouse_press(t_al *al)
{
	if (al->status == MENU)
		mouse_press_menu(al);
	if (al->status == EDIT)
		mouse_press_edit(al);
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

void		mouse_mv(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (mev.windowID == 1)
	{
		if (al->edit.stat == DRAWING)
		{
			al->sect->walls->x2 = mev.x - (mev.x % al->edit.zoom);
			al->sect->walls->y2 = mev.y - (mev.y % al->edit.zoom);
			// (void)al;
		}
	}
}

// void		convert_wall(t_al *al, t_wall *wall)
// {
// 	wall->x1++;
// 	wall->y1++;
// 	wall->x2++;
// 	wall->y2++;
// 	if (wall->next)
// 		convert_wall(al, wall->next);
// }

void		mouse_weel(t_al *al)
{
	// t_wall	*tmp;

	(void)al;
	// if (al->ev.wheel.y > 0) // scroll up
	// {
	// 	al->edit.zoom++;
	// 	if (al->wall->x2 != -1)
	// 	{
	// 		convert_wall(al, al->wall);
	// 	}
	// }	// printf("test up\n");
	// else if (al->ev.wheel.y < 0 && al->edit.zoom > 2)
	// 	al->edit.zoom--;
	// if (al->wall->x2 != -1)
		// convert_wall(al, al->wall);
	// scroll down
		// printf("test down\n");
	// if (al->ev.wheel.x > 0) // scroll right
	// 	printf("test up x\n");
	// else if (al->ev.wheel.x < 0)
	// 	printf("test down x\n");
}
