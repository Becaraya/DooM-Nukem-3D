/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:15:33 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/12 15:59:13 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	print_text(t_al *al, t_text text)
{
	SDL_Surface		*tmp;
	
	tmp = NULL;
	if (!(tmp = TTF_RenderText_Blended(al->font, text.str, text.clr)))
		yeet(al);
	if (SDL_BlitSurface(tmp, 0, al->surf_ed, text.where))
		yeet(al);
	else
		SDL_FreeSurface(tmp);

}

void	text(t_al *al)
{
	print_text(al, al->text.gen_map);
	al->sect ? print_text(al, al->text.sect_para) : 0;
	al->sect ? print_text(al, al->text.x_start) : 0;
	al->sect ? print_text(al, al->text.y_start) : 0;
	al->sect ? print_text(al, al->text.x_end) : 0;
	al->sect ? print_text(al, al->text.y_end) : 0;
	al->edit.stat == DRAWING ? print_text(al, al->text.cancel) : 0;
}

void	refresh(t_al *al)
{
	if (al->status == EDIT)
		text(al);
	if (SDL_UpdateWindowSurface(al->sdlwin))
		yeet(al);
	if (al->status == EDIT && (SDL_UpdateWindowSurface(al->win_ed)))
		yeet(al);
}
