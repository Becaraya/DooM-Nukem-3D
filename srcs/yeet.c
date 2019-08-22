/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/08/22 12:50:09 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	yeet(t_al *al)
{
	al->pix ? free(al->pix) : 0;
	al->ren ? SDL_DestroyRenderer(al->ren) : 0;
	al->tex ? SDL_DestroyTexture(al->tex) : 0;
	if (al->win)
	{
		SDL_DestroyWindow(al->win);
		SDL_Quit();
	}
	exit(0);
}
