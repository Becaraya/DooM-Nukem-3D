/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_funk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:43:49 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/06 15:20:27 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		mouse_press(t_al *al)
{
	if (al->status == GAME)
		pewpew(al);
	if (al->status == EDIT)
		mouse_press_edit(al);
	if (al->status == DEAD || al->status == WON)
		exit(0);
}

void		mouse_mv(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (al->status == GAME && mev.x != WIN_SIZEX / 2)
		al->play.dir = (al->play.dir + mev.xrel * 10) & D_2PIM;
	if (al->status == GAME && mev.y != WIN_SIZEY / 2)
		al->play.horizon = al->play.horizon + mev.yrel * 3;
	if (mev.windowID == 1)
	{
		if (al->edit.stat == DRAWING)
		{
			al->sect->walls->x2 = mev.x - (mev.x % al->edit.zoom);
			al->sect->walls->y2 = mev.y - (mev.y % al->edit.zoom);
		}
	}
}

void		mouse_weel(t_al *al)
{
	(void)al;
}
