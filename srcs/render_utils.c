/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:09:27 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 14:09:14 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

inline t_angle	d_atan2(double d1, double d2)
{
	d1 = atan2(d1, d2);
	d1 = d1 < 0 ? M_2PI + d1 : d1;
	return ((t_angle)(d1 * D_2PI / M_2PI));
}

inline t_angle	d_atan(double a)
{
	a = atan(a);
	a = a < 0 ? M_2PI + a : a;
	return ((t_angle)(a * D_2PI / M_2PI));
}

void			swapd(double *d1, double *d2)
{
	double tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

double			wall_len(t_walls *wall)
{
	double	tmp;

	tmp = (wall->x2 - wall->x1) * (wall->x2 - wall->x1);
	tmp += (wall->y2 - wall->y1) * (wall->y2 - wall->y1);
	return (sqrt(tmp));
}

t_tex			find_ent_tex(t_al *al, t_mob *ent)
{
	t_tex		tmp;
	unsigned	frame;

	if (ent->alive)
	{
		tmp.size_x = al->texgp[0].size_x;
		tmp.size_y = al->texgp[0].size_y;
		tmp.pix = al->texgp[0].or[sub_angle(ent->angle_to_player + D_PI_4 / 2,
				ent->dir) / D_PI_4].pix[al->anim >> 14];
	}
	else
	{
		frame = ent->anim / 65000;
		frame > 7 ? frame = 7 : 0;
		tmp = al->mob_death[frame];
	}
	return (tmp);
}
