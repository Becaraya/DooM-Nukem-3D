/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectanle_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:00:13 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/30 15:15:15 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		set_edit_menu_next_next(t_al *al)
{
	t_point		m;

	m = itop(al->ev.motion.x, al->ev.motion.y);
	if ((al->edit.stat >= SET_PLAYER && al->edit.stat <= MASS) ||
	(al->ev.motion.windowID == 2 && inr(itop(495, 240), itop(645, 285), m)))
	{
		put_rectangle(al->surf_ed, itop(495, 240), itop(645, 285), BLACK);
		if (al->edit.stat == LIFE || inr(itop(45, 320), itop(220, 365), m))
			put_rectangle(al->surf_ed, itop(45, 320), itop(220, 365), BLACK);
		if (al->edit.stat == POW || inr(itop(280, 320), itop(460, 365), m))
			put_rectangle(al->surf_ed, itop(280, 320), itop(460, 365), BLACK);
		if (al->edit.stat == WEAPON || inr(itop(495, 320), itop(645, 365), m))
			put_rectangle(al->surf_ed, itop(495, 320), itop(645, 365), BLACK);
		if (al->edit.stat == SIZE || inr(itop(45, 400), itop(220, 445), m))
			put_rectangle(al->surf_ed, itop(45, 400), itop(220, 445), BLACK);
		if (al->edit.stat == MASS || inr(itop(280, 400), itop(460, 445), m))
			put_rectangle(al->surf_ed, itop(280, 400), itop(460, 445), BLACK);
	}
}

void			set_edit_menu_next(t_al *al)
{
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 540), itop(220, 585),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_SPAWN
	|| al->edit.stat == SET_END)
		put_rectangle(al->surf_ed, itop(45, 540), itop(220, 585), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 540), itop(460, 585),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_BAD_PIG)
		put_rectangle(al->surf_ed, itop(280, 540), itop(460, 585), BLACK);
	if ((al->ev.motion.windowID == 2 && (inr(itop(495, 540), itop(645, 585),
	itop(al->ev.motion.x, al->ev.motion.y))))
	|| al->edit.stat == SELECT || al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itop(495, 540), itop(645, 585), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 605), itop(220, 650),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == LINK_MOD)
		put_rectangle(al->surf_ed, itop(45, 605), itop(220, 650), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 605), itop(460, 650),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == GRAVITY)
		put_rectangle(al->surf_ed, itop(280, 605), itop(460, 650), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 655), itop(493, 698),
				itop(al->ev.motion.x, al->ev.motion.y))))
		put_rectangle(al->surf_ed, itop(280, 655), itop(490, 695), BLACK);
	set_edit_menu_next_next(al);
}

void			global_menu_rectangle(t_al *al)
{
	if (al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itop(590, 15), itop(699, 48), BLACK);
	if (al->ev.motion.windowID == 2)
	{
		if (inr(itop(45, 125), itop(230, 170), itop(al->ev.motion.x,
			al->ev.motion.y)))
			put_rectangle(al->surf_ed, itop(45, 125), itop(230, 170), BLACK);
		if (inr(itop(280, 125), itop(460, 170), itop(al->ev.motion.x,
			al->ev.motion.y)))
			put_rectangle(al->surf_ed, itop(280, 125), itop(460, 170), BLACK);
		if (inr(itop(495, 125), itop(645, 170), itop(al->ev.motion.x,
			al->ev.motion.y)))
			put_rectangle(al->surf_ed, itop(495, 125), itop(645, 170), BLACK);
	}
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 240), itop(220, 285),
		itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_SECT
		|| al->edit.stat == SET_FLO_TEXT || al->edit.stat == SET_FLO_HEI
		|| al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_CEL_HEI)
		put_rectangle(al->surf_ed, itop(45, 240), itop(220, 285), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 240), itop(460, 285),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_WALL
	|| al->edit.stat == SET_WALL_TEXT)
		put_rectangle(al->surf_ed, itop(280, 240), itop(460, 285), BLACK);
}

void			sect_wall_menu_rectangle(t_al *al)
{
	if (al->edit.stat != SET_WALL_TEXT)
	{
		if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
		&& inr(itop(280, 400), itop(460, 445),
		itop(al->ev.motion.x, al->ev.motion.y)))
		|| al->edit.stat == SET_CEL_HEI))
			put_rectangle(al->surf_ed, itop(280, 400), itop(460, 445), BLACK);
		if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
		&& inr(itop(280, 320), itop(460, 365), itop(al->ev.motion.x,
		al->ev.motion.y))) || al->edit.stat == SET_CEL_TEXT))
			put_rectangle(al->surf_ed, itop(280, 320), itop(460, 365), BLACK);
		if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
		&& inr(itop(45, 400), itop(220, 445),
		itop(al->ev.motion.x, al->ev.motion.y)))
		|| al->edit.stat == SET_FLO_HEI))
			put_rectangle(al->surf_ed, itop(45, 400), itop(220, 445), BLACK);
		if (inr(itop(495, 320), itop(645, 365),
		itop(al->ev.motion.x, al->ev.motion.y)))
			put_rectangle(al->surf_ed, itop(495, 320), itop(645, 365), BLACK);
	}
}
