/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:15:11 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/23 15:10:42 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void														menu(t_al *al)
{
	(void)al;
	// refresh(al);
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
	al->dtime > 1000000 ? al->dtime = 1000000 : 0;
	al->anim += al->dtime * UINT16_MAX / 1000000;
	al->fire_anim += al->dtime;
	al->last_time = al->curr_time;
	al->tgt_time = al->last_time + 1000000 / al->fps;
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
			if (al->ev.type == SDL_MOUSEBUTTONDOWN)
				mouse_press(al);
			if (al->ev.type == SDL_MOUSEMOTION)
				mouse_mv(al);
			if (al->ev.type == SDL_MOUSEWHEEL)
				mouse_weel(al);
			if (al->ev.type == SDL_WINDOWEVENT)
				if (al->ev.window.event == SDL_WINDOWEVENT_CLOSE)
					yeet(al);
		}
		dtime(al);
		al->stat_fnc[al->status](al);
	}

}
