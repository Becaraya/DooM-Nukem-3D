/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sport_physics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:21:04 by pitriche          #+#    #+#             */
/*   Updated: 2019/09/25 10:00:58 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** run boy run, they try to catch you
*/

/*
** returns the power neccesary to sustain running at the current speed
*/

inline double	power_to_run(t_al *al)
{
	return (al->play.mass * al->g * al->play.gd_vel / 6);
}

/*
** consider jump is an instantaneous .25s power application
*/

void			jump(t_al *al)
{
	if (al->play.on_ground)
	{
		al->play.on_ground = 0;
		al->play.velz += sqrt(al->play.power * al->play.power_mult) / (1.41
				* sqrt(al->play.mass));
	}
}