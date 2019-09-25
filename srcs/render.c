/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/25 12:26:23 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		cast_ray(t_al *al, int x, t_rc_ray *ray)
{
	
}

void		render(t_al *al)
{
	t_rc_ray	ray;
	int 		x;

	x = 0;
	while (x < WIN_SIZEX)
	{
		cast_ray(al, x, &ray);
		//column(al, x, al->hitdst);
		x++;
	}
	//minimap(al);
	// printf("fps: %d\n", 1000000 / al->dtime);
	SDL_UpdateTexture(al->sdltex, 0, al->pix, WIN_SIZEX * sizeof(int));
	SDL_RenderCopy(al->sdlren, al->sdltex, 0, 0);
	SDL_RenderPresent(al->sdlren);
}
