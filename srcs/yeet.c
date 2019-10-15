/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/10 17:04:38 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** /!\ This only refresh first window
*/

void	refresh(t_al *al)
{
	if ((SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int)) < 0)
		|| (SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0) < 0))
		yeet(al);
	SDL_RenderPresent(al->sdlren);
}

/*
** al->sdlren ? SDL_DestroyRenderer(al->sdlren) : 0;
** al->ren_ ? SDL_DestroyRenderer(al->ren_) : 0;
** Il s'avere que ces ptit batars de l'arbalete de leurs morts, leaks. Donc on
** les met pas.
*/

void	yeet(t_al *al)
{
	al->pix ? free(al->pix) : 0;
	al->pix_ ? free(al->pix_) : 0;
	al->sdltex ? SDL_DestroyTexture(al->sdltex) : 0;
	al->tex_ ? SDL_DestroyTexture(al->tex_) : 0;
	if (al->sdlwin)
	{
		SDL_DestroyWindow(al->sdlwin);
		!al->win_ ? SDL_Quit() : 0;
	}
	if (al->win_)
	{
		SDL_DestroyWindow(al->win_);
		SDL_Quit();
	}
	exit(0);
}
