/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:50:00 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/21 16:38:58 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			set_edit(t_al *al)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	while (x < WIN_SIZEX)
	{
		while (y < WIN_SIZEY)
		{
			if (((x % (al->edit.zoom)) == 0)
				&& (y % (al->edit.zoom) == 0) && y > 0 && x > 0)
				al->pix[x + (y * WIN_SIZEX)] = WHITE;
			y++;
		}
		y = 0;
		x++;
	}
}

/*
**	SELECT,
**	DRAWING,
**	SET_SPAWN,
**	SET_BAD_PIG,

**	SET_FLO_TEXT,
**	SET_CEL_TEXT,

**	SET_FLO_HEI,
**	SET_CEL_HEI,

**	SET_WALL_TEXT,
**	LINK_MOD,
**	EDIT_WALL,
**	EDIT_SECT
*/


void			get_hei(t_al *al)
{
	t_sector	*tmp;
	char		*t;
	int			i;

	t = NULL;
	i = al->edit.index_sect - 1;
	tmp = al->sect;
	al->text.ce_hei_num.str ? ft_strdel(&al->text.ce_hei_num.str) : 0;
	al->text.ce_hei_num.where ? ft_rectdel(&al->text.ce_hei_num.where) : 0;
	al->text.fl_hei_num.str ? ft_strdel(&al->text.fl_hei_num.str) : 0;
	al->text.fl_hei_num.where ? ft_rectdel(&al->text.fl_hei_num.where) : 0;
	while (i--)
		tmp = tmp->next;
	if (al->edit.stat == SET_FLO_HEI)
	{
		t = dtoa_doom(tmp->fl_hei);
		if (set_text(&al->text.fl_hei_num, (tmp->fl_hei) ? t : "0", get_rect(570, 410),
		add_color(TEXT_EDITOR)) == -1)
			yeet(al);
	}
	else
	{
		t = dtoa_doom(tmp->ce_hei);
		if (set_text(&al->text.ce_hei_num, (tmp->ce_hei) ? t : "0", get_rect(570, 410),
		add_color(TEXT_EDITOR)) == -1)
			yeet(al);
	}
	free(t);
}

void			set_edit_menu_next_next(t_al *al)
{
	t_point mouse;

	mouse = itop(al->ev.motion.x, al->ev.motion.y);
	if ((al->edit.stat >= SET_PLAYER && al->edit.stat <= MASS )||
	(al->ev.motion.windowID == 2
	&& inr(itop(495, 240), itop(645, 285), mouse)))
	{
		put_rectangle(al->surf_ed, itop(495, 240), itop(645, 285), BLACK);
		if (al->edit.stat == LIFE || inr(itop(45, 320), itop(220, 365), mouse))
			put_rectangle(al->surf_ed, itop(45, 320), itop(220, 365), BLACK);
		if (al->edit.stat == POW || inr(itop(280, 320), itop(460, 365), mouse))
			put_rectangle(al->surf_ed, itop(280, 320), itop(460, 365),BLACK);
		if (al->edit.stat == WEAPON || inr(itop(495, 320), itop(645, 365), mouse))
			put_rectangle(al->surf_ed, itop(495, 320), itop(645, 365),BLACK);
		if (al->edit.stat == SIZE || inr(itop(45, 400), itop(220, 445), mouse))
			put_rectangle(al->surf_ed, itop(45, 400), itop(220, 445), BLACK);
		if (al->edit.stat == MASS || inr(itop(280, 400), itop(460, 445), mouse))
			put_rectangle(al->surf_ed, itop(280, 400), itop(460, 445), BLACK);
	}
}

void			set_edit_menu_next(t_al *al)
{
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 540), itop(220, 585),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_SPAWN)
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
	set_edit_menu_next_next(al);
}

void			set_edit_menu(t_al *al)
{
	ft_memset(al->pix_ed, LIGHT_GREY, WIN_EDIT_SIZEX * WIN_EDIT_SIZEY *
		sizeof(int));
	if (al->sect && al->sect->walls)
	{
		if (al->edit.stat == SET_FLO_HEI || al->edit.stat == SET_CEL_HEI)
			get_hei(al);
		print_co(al);
	}
	if (al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itop(590, 15), itop(699, 48), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 240), itop(220, 285),
		itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_SECT
		|| al->edit.stat == SET_FLO_TEXT || al->edit.stat == SET_FLO_HEI
		|| al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_CEL_HEI)
		put_rectangle(al->surf_ed, itop(45, 240), itop(220, 285), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 240), itop(460, 285),
	itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_WALL
	|| al->edit.stat == SET_WALL_TEXT)
		put_rectangle(al->surf_ed, itop(280, 240), itop(460, 285), BLACK);
	if (al->edit.stat == EDIT_WALL || al->edit.stat == EDIT_SECT
		|| al->edit.stat == SET_FLO_TEXT || al->edit.stat == SET_FLO_HEI
		|| al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_CEL_HEI
		|| al->edit.stat == SET_WALL_TEXT)
	{
		if (al->edit.stat != SET_WALL_TEXT)
		{
			if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
			&& inr(itop(280, 400), itop(460, 445),
			itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_CEL_HEI))
				put_rectangle(al->surf_ed, itop(280, 400), itop(460, 445), BLACK);
			if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
			&& inr(itop(280, 320), itop(460, 365), itop(al->ev.motion.x,
			al->ev.motion.y))) || al->edit.stat == SET_CEL_TEXT))
				put_rectangle(al->surf_ed, itop(280, 320), itop(460, 365), BLACK);
			if (al->edit.stat != EDIT_WALL && ((al->ev.motion.windowID == 2
			&& inr(itop(45, 400), itop(220, 445),
			itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_FLO_HEI))
				put_rectangle(al->surf_ed, itop(45, 400), itop(220, 445), BLACK);
		}
		if ((al->ev.motion.windowID == 2 && inr(itop(45, 320), itop(220, 365),
		itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == SET_FLO_TEXT
		|| al->edit.stat == SET_WALL_TEXT)
			put_rectangle(al->surf_ed, itop(45, 320), itop(220, 365), BLACK);
	}
	set_edit_menu_next(al);
}
