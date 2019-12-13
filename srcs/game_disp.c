/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_disp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:05:51 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/13 13:48:30 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		rotate(t_al *al)
{
	if (al->k.left)
		al->play.dir = sub_angle(al->play.dir, (LOOK_SENS * D_2PI / 2500) *
		al->dtime / 1000000);
	if (al->k.righ)
		al->play.dir = add_angle(al->play.dir, (LOOK_SENS * D_2PI / 2500) *
		al->dtime / 1000000);
	if (al->k.up)
		al->play.horizon -= LOOK_SENS * al->dtime / 1000000;
	if (al->k.down)
		al->play.horizon += LOOK_SENS * al->dtime / 1000000;
	al->play.horizon < -HORIZON_LIMIT ? al->play.horizon = -HORIZON_LIMIT : 0;
	al->play.horizon > HORIZON_LIMIT ? al->play.horizon = HORIZON_LIMIT : 0;
}

/*
** mock me all you want but you have a better way i'm all ears
** return 69420 in case of any contradicting keys
*/

t_angle		angle(t_al *al)
{
	t_angle dir;

	dir = al->play.dir;
	if (al->k.w && !al->k.a && !al->k.s && !al->k.d)
		return (dir & D_2PIM);
	if (!al->k.w && al->k.a && !al->k.s && !al->k.d)
		return (sub_angle(dir, D_PI_2));
	if (!al->k.w && !al->k.a && al->k.s && !al->k.d)
		return (add_angle(dir, D_PI));
	if (!al->k.w && !al->k.a && !al->k.s && al->k.d)
		return (add_angle(dir, D_PI_2));
	if (al->k.w && al->k.a && !al->k.s && !al->k.d)
		return (sub_angle(dir, D_PI_4));
	if (!al->k.w && al->k.a && al->k.s && !al->k.d)
		return (sub_angle(dir, D_PI - D_PI_4));
	if (!al->k.w && !al->k.a && al->k.s && al->k.d)
		return (add_angle(dir, D_PI - D_PI_4));
	if (al->k.w && !al->k.a && !al->k.s && al->k.d)
		return (add_angle(dir, D_PI_4));
	return (69420);
}

/*
** smooth deceleration, become frame dependant under 1 m/s and stop at .1
*/

void		deceleration(t_al *al)
{
	double wack;

	wack = 4.0 * al->dtime / 1000000.0;
	wack = wack > 0.9 ? 0.9 : wack;
	if (al->play.gd_vel < 1)
		wack = 0.25;
	if (al->play.gd_vel < 0.1)
	{
		al->play.gd_vel = 0;
		al->play.velx = 0;
		al->play.vely = 0;
	}
	al->play.velx *= 1 - wack;
	al->play.vely *= 1 - wack;
	al->play.gd_vel = sqrt(al->play.velx * al->play.velx + al->play.vely *
		al->play.vely);
}

/*
** 0.3 is the power reduction factor when running in non forward direction
** catch angle's 69420 return and set the input power to null
*/

void		acceleration(t_al *al)
{
	double	net_power;
	double	net_force;
	double	net_accel;
	t_angle	dir_force;

	net_power = al->play.power * (al->k.w ? 1 : 0.4) * al->play.power_mult
	- power_to_run(al);
	dir_force = angle(al);
	if (dir_force == 69420 || net_power < 0)
	{
		deceleration(al);
		return ;
	}
	net_force = net_power / (al->play.gd_vel > 1 ? al->play.gd_vel : 1);
	net_accel = net_force / (al->play.mass ? al->play.mass : 1);
	al->play.gd_vel += net_accel * al->dtime / 1000000;
	al->play.velx = al->sin[dir_force] * al->play.gd_vel;
	al->play.vely = al->cos[dir_force] * al->play.gd_vel;
}

void		displacement(t_al *al)
{
	if (al->dtime > 1)
		ft_nop_player(al, 0, al->play.velx * al->dtime / 1000000, al->play.vely
		* al->dtime / 1000000);
	al->play.posz += al->play.velz * al->dtime / 1000000;
	al->play.eyez += al->play.velz * al->dtime / 1000000;
	if (al->dtime > 1)
		ft_nop(al, &al->ent[0], al->ent[0].velx * al->dtime / 1000000,
		al->ent[0].vely * al->dtime / 1000000);
	if (al->play.posz < al->sec[al->play.csec].fl_hei)
	{
		al->play.posz = al->sec[al->play.csec].fl_hei;
		al->play.eyez = al->sec[al->play.csec].fl_hei + al->play.size
		- PLAYER_EYE_TOP;
		al->play.velz = 0;
		al->play.on_ground = 1;
	}
	if (al->play.posz + al->play.size > al->sec[al->play.csec].ce_hei)
	{
		al->play.posz = al->sec[al->play.csec].ce_hei - al->play.size;
		al->play.eyez = al->sec[al->play.csec].ce_hei - PLAYER_EYE_TOP;
		al->play.velz = 0;
	}
	if (al->sec[al->play.csec].ce_hei - al->sec[al->play.csec].fl_hei <
		al->play.size)
		al->play.alive = 0;
}
