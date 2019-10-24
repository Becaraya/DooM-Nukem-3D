/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/24 16:31:08 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** /!\ This only refresh first window
*/

	// // if ((SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int)) < 0)
	// // 	|| (SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0) < 0))
	// // 	yeet(al);
	// // SDL_RenderPresent(al->sdlren);
	// // SDL_LockSurface(al->sdlsurf);

    // // SDL_memset(al->sdlsurf->pixels, 0, al->sdlsurf->h * al->sdlsurf->pitch);

	// // ft_memcpy(al->surf_->pixels, al->pix_, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	
    // SDL_UnlockSurface(al->sdlsurf);

void	print_text(t_al *al)
{
	SDL_Rect		where;
	SDL_Surface		*tmp;
	char			*segm;
	
	where.x = 0;
	where.y = 0;
	if (!(segm = ft_strdup("TEST")))
		yeet(al);
	if (!(tmp = TTF_RenderText_Solid(al->font, segm, al->color)))
		yeet(al);
	if (SDL_BlitSurface(tmp, 0, al->surf_, &where))
		yeet(al);
	else
		SDL_FreeSurface(tmp);
	ft_strdel(&segm);
}

void	refresh(t_al *al)
{
	// ft_memcpy(al->sdlsurf->pixels, al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	print_text(al);
	SDL_UpdateWindowSurface(al->sdlwin);
	SDL_UpdateWindowSurface(al->win_);
	// ft_bzero(al->sdlsurf->pixels, sizeof(void *) * WIN_SIZEX * WIN_SIZEY);
	// ft_bzero(al->surf_->pixels, sizeof(void *) * WIN_EDIT_SIZEX * WIN_EDIT_SIZEY);
}

void	yeet(t_al *al)
{
	// al->pix ? free(al->pix) : 0;
	// al->pix_ ? free(al->pix_) : 0;
	al->font ? TTF_CloseFont(al->font) : 0;
	al->ttf_st ? TTF_Quit() : 0;
	// al->sdltex ? SDL_DestroyTexture(al->sdltex) : 0;
	// al->tex_ ? SDL_DestroyTexture(al->tex_) : 0;
	al->sdlsurf ? SDL_FreeSurface(al->sdlsurf) : 0;
	al->surf_ ? SDL_FreeSurface(al->surf_) : 0;
	al->win_ ? SDL_DestroyWindow(al->win_) : 0;
	if (al->sdlwin)
	{
		SDL_DestroyWindow(al->sdlwin);
		SDL_Quit();
	}
	exit(0);
}
