/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:15:11 by becaraya          #+#    #+#             */
/*   Updated: 2019/08/29 16:19:03 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom-nukem.h"

void		menu(t_al *al)
{

	for (int i = 0; i < 1280; i++){
		for (int j = 0; j < 720; j++){
			al->pix[WIN_SIZEX * j + i] = al->txt.s_menu[j * 1280 + i];// 0x34652864;//
		}
	}
	SDL_UpdateTexture(al->tex, 0, al->pix, WIN_SIZEX * sizeof(int));
	SDL_RenderCopy(al->ren, al->tex, 0, 0);
	SDL_RenderPresent(al->ren);
	//refresh(al);
}

static void	dtime(t_al *al)
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
	al->last_time = al->curr_time;
	al->tgt_time = al->last_time + 1000000 / al->fps;
}

static void	stat(t_al *al)
{
	if (al->status == ST_MENU)
		menu(al);
}

void		main_loop(t_al *al)
{
	while (1)
	{
		while (SDL_PollEvent(&al->ev) != 0)
		{
			al->ev.type == SDL_QUIT ? yeet(al) : 0;
			if ((al->ev.type == SDL_KEYDOWN || al->ev.type == SDL_KEYUP) &&
				!al->ev.key.repeat)
				key_func(al);
			if (al->ev.type == SDL_MOUSEMOTION)
				mouse_func(al);
			if (al->ev.type == SDL_MOUSEBUTTONDOWN)
				mouse_press(al);
		}
		dtime(al);
		stat(al);
	}
}
