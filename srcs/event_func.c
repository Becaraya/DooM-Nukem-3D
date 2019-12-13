/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 09:18:54 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 23:23:55 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
