/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:11:26 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/25 12:35:08 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	rotate(t_al *al)
{
	if (al->k.left)
		al->play.dir -= LOOK_SENS * al->dtime / 1000000;
	if (al->k.righ)
		al->play.dir += LOOK_SENS * al->dtime / 1000000;
	while (al->play.dir > M_2PI)
		al->play.dir -= M_2PI;
	while (al->play.dir < 0)
		al->play.dir += M_2PI;
	// al->k.left || al->k.righ ?
	// printf("%.3f, dtime:%d\n", al->play.dir, al->dtime) : 0;
}


/*
** mock me all you want but you have a better way i'm all ears
** return NaN in case of any contradicting keys
*/

static double	angle(t_al *al)
{
	double dir;

	dir = al->play.dir;
	if (al->k.w && !al->k.a && !al->k.s && !al->k.d)
		return (dir);
	if (!al->k.w && al->k.a && !al->k.s && !al->k.d)
		return (dir - M_PI_2);
	if (!al->k.w && !al->k.a && al->k.s && !al->k.d)
		return (dir + M_PI);
	if (!al->k.w && !al->k.a && !al->k.s && al->k.d)
		return (dir + M_PI_2);
	if (al->k.w && al->k.a && !al->k.s && !al->k.d)
		return (dir - M_PI_4);
	if (!al->k.w && al->k.a && al->k.s && !al->k.d)
		return (dir - M_PI + M_PI_4);
	if (!al->k.w && !al->k.a && al->k.s && al->k.d)
		return (dir + M_PI - M_PI_4);
	if (al->k.w && !al->k.a && !al->k.s && al->k.d)
		return (dir + M_PI_4);
	return (NAN);
}

/*
** smooth deceleration, become frame dependant under 1 m/s and stop at .1
*/

static void		deceleration(t_al *al)
{
	double wack;

	wack = 0.95 * al->dtime / 1000000;
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
** catch angle's NaN return and set the input power to null
*/

static void		acceleration(t_al *al)
{
	double net_power;
	double net_force;
	double net_accel;
	double dir_force;

	net_power = al->play.power * (al->k.w ? 1 : 0.3) * al->play.power_mult
	- power_to_run(al);
	dir_force = angle(al);
	if (dir_force != dir_force)
	{
		deceleration(al);
		return ;
	}
	net_force = net_power / (al->play.gd_vel > 1 ? al->play.gd_vel : 1);
	net_accel = net_force / (al->play.mass ? al->play.mass : 1);
	printf("pow>%f ", net_power);
	printf("force>%f ", net_force);
	printf("accel>%f\n", net_accel);
	al->play.velx += sin(dir_force) * net_accel * al->dtime / 1000000;
	al->play.vely += cos(dir_force) * net_accel * al->dtime / 1000000;
	al->play.gd_vel = sqrt(al->play.velx * al->play.velx + al->play.vely *
		al->play.vely);

	//al->k.w || al->k.a || al->k.s || al->k.d ?
	//printf("x%.1f y%.1f\n", al->play.posx, al->play.posy) : 0;
}

/*
**  apply displacment according to velocities and collisions (soon)
*/

static void		displacement(t_al *al)
{
	al->play.posx += al->play.velx * al->dtime / 1000000;
	al->play.posy += al->play.vely * al->dtime / 1000000;
	al->play.posz += al->play.velz * al->dtime / 1000000;
	if (al->play.posz < al->play.csec->fl_hei)
	{
		al->play.posz = al->play.csec->fl_hei;
		al->play.velz = 0;
		al->play.on_ground = 1;
	}
	// eventually add collision and physics
}

static void		flyyyy(t_al *al)
{
	al->play.velz -= al->g * al->dtime / 1000000;
}

void		game(t_al *al)
{
	printf("x%.1fm y%.1fm z%.1fcm speed>%.1fkm/h\n", al->play.posx, al->play.posy, al->play.posz*100, al->play.gd_vel * 3.6);
	rotate(al);
	if (al->play.on_ground)
		acceleration(al);
	else
		flyyyy(al);
	displacement(al);
	render(al);
}
