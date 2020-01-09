/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/09 16:39:31 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"



void		draw_hud(t_al *al)
{
	unsigned x;
	unsigned y;

	y = 0;
	while(y < al->heart.size_y)
	{
		x = 0;
		while(x < al->heart.size_x)
		{
			if (al->heart.pix[x + ((al->heart.size_y - y - 1) *
				al->heart.size_x)])
			al->pix[x + 20 + ((y + 20) * WIN_SIZEX)] = al->heart.pix[x +
				((al->heart.size_y - y - 1) * al->heart.size_x)];
			x++;
		}
		y++;
	}

	
}

void		render(t_al *al)
{
	t_rc_ray	ray;
	int			x;

	al->wall_scale = 0.1624 * D_2PI / al->fov;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	x = 0;
	while (x < WIN_SIZEX)
	{
		ray.nb_hits = 0;
		ray.x = x;
		cast_ray(al, (t_angle)(atan(al->fov * (x - (WIN_SIZEX / 2)) /
					WIN_SIZEX) / M_2PI * D_2PI + al->play.dir) & D_2PIM, &ray);
		column(al, &ray);
		x++;
	}
	draw_map(al);
	pimp_cross(al);
	draw_hud(al);
	ft_putstr(" FPS:");
	ft_putnbr(1000000 / al->dtime);
	refresh(al);
}
