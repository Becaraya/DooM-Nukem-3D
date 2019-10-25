/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/25 12:39:54 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** /!\ This only refresh first window
*/

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
	if (SDL_BlitSurface(tmp, 0, al->surf_ed, &where))
		yeet(al);
	else
		SDL_FreeSurface(tmp);
	ft_strdel(&segm);
}

void	refresh(t_al *al)
{
	print_text(al);
	if (SDL_UpdateWindowSurface(al->sdlwin))
		yeet(al);
	if (al->status == EDIT && (SDL_UpdateWindowSurface(al->win_ed)))
		yeet(al);
		
}

void	yeet(t_al *al)
{
	al->font ? TTF_CloseFont(al->font) : 0;
	al->ttf_st ? TTF_Quit() : 0;
	al->sdlsurf ? SDL_FreeSurface(al->sdlsurf) : 0;
	al->surf_ed ? SDL_FreeSurface(al->surf_ed) : 0;
	al->win_ed ? SDL_DestroyWindow(al->win_ed) : 0;
	if (al->sdlwin)
	{
		SDL_DestroyWindow(al->sdlwin);
		SDL_Quit();
	}
	exit(0);
}
