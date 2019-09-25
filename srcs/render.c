/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/22 15:58:31 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		render(t_al *al)
{
	int x;

	x = 0;
	while (x < WIN_SIZEX)
	{
		//cast_ray(al, x);
		//column(al, x, al->hitdst);
		x++;
	}
	//minimap(al);
	// printf("fps: %d\n", 1000000 / al->dtime);
	SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int));
	SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0);
	SDL_RenderPresent(al->sdlren);
}
