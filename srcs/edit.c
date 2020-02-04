/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/04 16:20:14 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_walls			*get_co_wal(t_al *al)
{
	t_sector				*tmp_s;
	t_walls					*tmp_w;
	int						i;
	int						j;

	i = 0;
	j = 0;
	tmp_s = al->sect;
	while ((al->nb_sec - i) > al->edit.index_sect + 1)
	{
		tmp_s = tmp_s->next;
		i++;
	}
	tmp_w = tmp_s->walls;
	while (tmp_s->nb_wal - j > al->edit.index_wall + 1)
	{
		tmp_w = tmp_w->next;
		j++;
	}
	return (tmp_w);
}

void			print_co(t_al *al)
{
	char					*tmp;

	tmp = ft_itoa(al->edit.index_sect);
	ft_strdel(&al->text.sect_index.str);
	al->text.sect_index.str = ft_strjoin("Sector ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(al->edit.index_wall + 1);
	ft_strdel(&al->text.wall_index.str);
	al->text.wall_index.str = ft_strjoin("Wall ", tmp);
	ft_strdel(&tmp);
}

void			interactive_arrow_sector(t_al *al, SDL_MouseMotionEvent mev)
{
	if (al->edit.index_sect > 1)
		draw_triangle(itop(160, 30), -1, al->surf_ed, inr(itop(145, 15),
		itop(175, 47), itop(mev.x, mev.y)) ? BLACK : WHITE);
	if (al->edit.index_sect < al->nb_sec)
		draw_triangle(itop(180, 30), 1, al->surf_ed, inr(itop(176, 15),
		itop(195, 47), itop(mev.x, mev.y)) ? BLACK : WHITE);
	if (al->edit.index_wall > 0)
		draw_triangle(itop(160, 69), -1, al->surf_ed, inr(itop(145, 58),
		itop(175, 88), itop(mev.x, mev.y)) ? BLACK : WHITE);
	if (al->edit.index_wall < nb_wall(al) - 1)
		draw_triangle(itop(180, 69), 1, al->surf_ed, inr(itop(176, 58),
		itop(195, 88), itop(mev.x, mev.y)) ? BLACK : WHITE);
}

void			interactive_arrow(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (al->sect)
		interactive_arrow_sector(al, mev);
	if (al->edit.stat == SET_CEL_HEI || al->edit.stat == SET_FLO_HEI
		|| (al->edit.stat >= LIFE && al->edit.stat <= MASS))
	{
		draw_triangle(itop(535, 420), -1, al->surf_ed, inr(itop(520, 410),
		itop(545, 435), itop(mev.x, mev.y)) ? BLACK : WHITE);
		draw_triangle(itop(640, 420), 1, al->surf_ed, inr(itop(630, 410),
		itop(660, 435), itop(mev.x, mev.y)) ? BLACK : WHITE);
	}
	if (al->edit.stat == GRAVITY)
	{
		draw_triangle(itop(535, 635), -1, al->surf_ed, inr(itop(520, 625),
		itop(545, 660), itop(mev.x, mev.y)) ? BLACK : WHITE);
		draw_triangle(itop(640, 635), 1, al->surf_ed, inr(itop(630, 615),
		itop(660, 660), itop(mev.x, mev.y)) ? BLACK : WHITE);
	}
}

void			editor(t_al *al)
{
	set_edit(al);
	ft_memset(al->pix_ed, LIGHT_GREY, WIN_EDIT_SIZEX * WIN_EDIT_SIZEY *
		sizeof(int));
	if (al->edit.stat == SET_WALL_TEXT ||
	al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_FLO_TEXT)
		tex_menu(al);
	else
		set_edit_menu(al);
	if (al->sect)
	{
		draw_sect(al, al->sect);
		draw_sect_index(al, al->sect, al->nb_sec);
	}
	interactive_arrow(al);
	pig_pos(al);
	refresh(al);
}
