/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/19 20:46:02 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	refresh(t_al *al)
{
	if ((SDL_UpdateTexture(al->tex, 0, al->pix, WIN_SIZEX * sizeof(int)) < 0)
		|| (SDL_RenderCopy(al->ren, al->tex, 0, 0) < 0))
		yeet(al);
	SDL_RenderPresent(al->ren);
}

int		yeet(t_al *al)
{
	al->pix ? free(al->pix) : 0;
	al->pix_ ? free(al->pix_) : 0;
	al->ren ? SDL_DestroyRenderer(al->ren) : 0;
	al->ren_ ? SDL_DestroyRenderer(al->ren_) : 0;
	al->tex ? SDL_DestroyTexture(al->tex) : 0;
	al->tex_ ? SDL_DestroyTexture(al->tex_) : 0;
	if (al->win)
	{
		SDL_DestroyWindow(al->win);
		SDL_DestroyWindow(al->win_);
		SDL_Quit();
	}
	exit(0);
}
