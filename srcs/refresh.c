/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:15:33 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/24 17:48:23 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	refresh(t_al *al)
{
	if (al->status == EDIT)
		text(al);
	if (al->k.t == 1 && al->status == GAME)
		print_text(al, al->text.t, al->sdlsurf);
	if (SDL_UpdateWindowSurface(al->sdlwin))
		yeet(al);
	if (al->status == EDIT && (SDL_UpdateWindowSurface(al->win_ed)))
		yeet(al);
}
