/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:43:49 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/20 12:46:05 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		mouse_press_menu(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.clicks == 1)
	{
		if (bev.button == SDL_BUTTON_LEFT)
		{
			if (bev.y > 228 && bev.y < 315 && bev.x > 766 && bev.x < 940)
				printf("GO\n");
			if (bev.y > 472 && bev.y < 574 && bev.x > 772 && bev.x < 943)
				printf("QUIT\n");
			if (bev.y > 347 && bev.y < 444 && bev.x > 720 && bev.x < 1004)
				printf("SETTING\n");
		}
	}
}

void		mouse_press(t_al *al)
{
	if (al->status == MENU)
		mouse_press_menu(al);
	if (al->status == EDIT)
		mouse_press_edit(al);
}

void		mouse_mv(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (mev.x != WIN_SIZEX / 2)
		al->play.dir = (al->play.dir + mev.xrel * 10) & D_2PIM;
	if (mev.y != WIN_SIZEY / 2)
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
