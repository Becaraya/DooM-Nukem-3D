/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:55:59 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/23 18:43:47 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		shoot(t_al *al)
{
	int tmp;

	tmp = 60000;

	if (al->fire_anim < 100000)
		al->f = al->weapon[1];
	else if (al->fire_anim < 100000 + 1 * tmp)
		al->f = al->weapon[2];
	else if (al->fire_anim < 100000 + 2 * tmp)
		al->f = al->weapon[3];
	else if (al->fire_anim < 100000 + 3 * tmp)
		al->f = al->weapon[4];
	else if (al->fire_anim < 100000 + 5 * tmp)
		al->f = al->weapon[5];
	else if (al->fire_anim < 100000 + 7 * tmp)
		al->f = al->weapon[6];
	else if (al->fire_anim < 100000 + 9 * tmp)
		al->f = al->weapon[5];
	else if (al->fire_anim < 100000 + 11 * tmp)
		al->f = al->weapon[4];
	else if (al->fire_anim < 100000 + 13 * tmp)
		al->f = al->weapon[3];
	else
		al->f = al->weapon[0];
}

void		draw_wapon(t_al *al)
{
	t_tex		tex;
	unsigned	x;
	unsigned	y;
	t_point		win;
	unsigned	tmp;
	double		scale;

	scale = 2.5;
	tex = al->f;
	y = 0;
	win.x = WIN_SIZEX / 2 + (tex.size_x * scale) / 2 - 100;
	win.y = WIN_SIZEY - (tex.size_y * scale);
	while (y < (tex.size_y * scale))
	{
		x = 0;
		while (x < (tex.size_x * scale))
		{
			tmp = tex.pix[(unsigned)(y / scale) * (tex.size_x) + (unsigned)(x / scale)];
			if (tmp != 41704)
				al->pix[(y + win.y) * WIN_SIZEX + x + win.x] = tmp;
			x++;
		}
		y++;
	}
}

void		draw_hud(t_al *al)
{
	unsigned	x;
	unsigned	y;
	int 		a;

	a = al->play.alive;
	while (a)
	{
		y = 0;
		while(y < al->h.size_y)
		{
			x = 0;
			while(x < al->h.size_x)
			{
				if (al->h.pix[x + ((al->h.size_y - y - 1) *
					al->h.size_x)])
					al->pix[x + (70 * a) + ((y + 20) * WIN_SIZEX)] =
					al->h.pix[x + ((al->h.size_y - y - 1) * al->h.size_x)];
				x++;
			}
			y++;
		}
		a--;
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
	shoot(al);
	draw_wapon(al);
	ft_putstr(" fps:");
	ft_putnbr(1000000 / al->dtime);
	refresh(al);
}
