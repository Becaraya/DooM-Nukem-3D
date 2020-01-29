/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:50:00 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/29 15:08:34 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			print_spawn_end(t_al *al)
{
	int		tmpx;
	int		tmpy;

	tmpy = al->play.posy * -10 + (WIN_SIZEY / 2);
	tmpx = al->play.posx * 10 + (WIN_SIZEX / 2);
	put_rectangle(al->sdlsurf, itop(tmpx - 1, tmpy - 1),
	itop(tmpx + 1, tmpy + 1), RED);
	if (!al->edit.sect_end)
	{
		put_rectangle(al->sdlsurf, itop(al->end_sect.x - 1, al->end_sect.y - 1),
		itop(al->end_sect.x + 1, al->end_sect.y + 1), BLUE);
	}
}

void			set_edit(t_al *al)
{
	int				x;
	int				y;

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
	put_rectangle(al->sdlsurf, itop(WIN_SIZEX / 2 - 2, WIN_SIZEY / 2 - 2),
	itop(WIN_SIZEX / 2 + 2, WIN_SIZEY / 2 + 2), GREEN);
	print_spawn_end(al);
}

void			get_hei(t_al *al)
{
	t_sector		*tmp;
	char			*t;
	unsigned int	i;

	i = 0;
	tmp = al->sect;
	free_text_hei_num(al);
	while (al->edit.index_sect + i++ < al->nb_sec)
		tmp = tmp->next;
	if (al->edit.stat == SET_FLO_HEI)
	{
		t = dtoa_doom(tmp->fl_hei);
		if (set_text(&al->text.fl_hei_num, (tmp->fl_hei) ? t : "0",
		get_rect(570, 410), add_color(TEXT_EDITOR)) == -1)
			yeet(al);
	}
	else
	{
		t = dtoa_doom(tmp->ce_hei);
		if (set_text(&al->text.ce_hei_num, (tmp->ce_hei) ? t : "0",
		get_rect(570, 410), add_color(TEXT_EDITOR)) == -1)
			yeet(al);
	}
	free(t);
}

void			get_player_stat(t_al *al)
{
	if (al->edit.stat >= LIFE && al->edit.stat <= MASS)
	{
		al->text.player_value.str ? ft_strdel(&al->text.player_value.str) : 0;
		if (al->edit.stat == LIFE)
			al->text.player_value.str = ft_itoa((int)al->play.alive);
		if (al->edit.stat == POW)
			al->text.player_value.str = dtoa_doom(al->play.power_mult);
		if (al->edit.stat == WEAPON)
			al->text.player_value.str = ft_itoa(0);
		if (al->edit.stat == SIZE)
			al->text.player_value.str = dtoa_doom(al->play.size);
		if (al->edit.stat == MASS)
			al->text.player_value.str = dtoa_doom(al->play.mass);
	}
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
	get_player_stat(al);
	global_menu_rectangle(al);
	if (al->edit.stat == EDIT_WALL || al->edit.stat == EDIT_SECT
		|| al->edit.stat == SET_FLO_TEXT || al->edit.stat == SET_FLO_HEI
		|| al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_CEL_HEI
		|| al->edit.stat == SET_WALL_TEXT)
	{
		sect_wall_menu_rectangle(al);
		if ((al->ev.motion.windowID == 2 && inr(itop(45, 320), itop(220, 365),
		itop(al->ev.motion.x, al->ev.motion.y)))
		|| al->edit.stat == SET_FLO_TEXT || al->edit.stat == SET_WALL_TEXT)
			put_rectangle(al->surf_ed, itop(45, 320), itop(220, 365), BLACK);
	}
	set_edit_menu_next(al);
}
