/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:15:11 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 11:40:51 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** wonderfully empty function
*/

void														menu(t_al *al)
{
	(void)al;
}

static void													anims(t_al *al)
{
	unsigned		i;

	al->anim += al->dtime * UINT16_MAX / 1000000;
	al->fire_anim += al->dtime;
	i = 0;
	while (i < al->nb_ent)
		al->ent[i++].anim += al->dtime;
}

static void													dtime(t_al *al)
{
	struct timeval	tv;

	gettimeofday(&tv, (void *)al->v0id);
	al->curr_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (al->curr_time < al->tgt_time)
	{
		usleep(al->tgt_time - al->curr_time);
		al->curr_time = al->tgt_time;
	}
	al->dtime = al->curr_time - al->last_time;
	al->dtime > 100000 ? al->dtime = 100000 : 0;
	al->last_time = al->curr_time;
	al->tgt_time = al->last_time + 1000000 / al->fps;
	anims(al);
}

void														main_loop(t_al *al)
{
	while (1)
	{
		while (SDL_PollEvent(&al->ev) != 0)
		{
			al->ev.type == SDL_QUIT ? yeet(al) : 0;
			if ((al->ev.type == SDL_KEYDOWN || al->ev.type == SDL_KEYUP) &&
				!al->ev.key.repeat)
				key_func(al);
			else if (al->ev.type == SDL_MOUSEBUTTONDOWN)
				mouse_press(al);
			else if (al->ev.type == SDL_MOUSEMOTION)
				mouse_mv(al);
			else if (al->ev.type == SDL_MOUSEWHEEL)
				mouse_weel(al);
			else if (al->ev.type == SDL_WINDOWEVENT)
				if (al->ev.window.event == SDL_WINDOWEVENT_CLOSE)
					yeet(al);
		}
		dtime(al);
		al->stat_fnc[al->status](al);
	}
}
