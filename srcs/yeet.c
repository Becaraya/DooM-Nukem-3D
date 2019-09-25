/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/20 12:45:34 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	refresh(t_al *al)
{
	if ((SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int)) < 0)
		|| (SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0) < 0))
		yeet(al);
	SDL_RenderPresent(al->sdlren);
}

void	yeet(t_al *al)
{
	al->pix ? free(al->pix) : 0;
	al->sdlren ? SDL_DestroyRenderer(al->sdlren) : 0;
	al->sdltex ? SDL_DestroyTexture(al->sdltex) : 0;
	if (al->sdlwin)
	{
		SDL_DestroyWindow(al->sdlwin);
		SDL_Quit();
	}
	exit(0);
}
