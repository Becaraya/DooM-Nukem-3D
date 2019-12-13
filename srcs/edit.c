/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/13 00:41:25 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <stdlib.h>

void			assign_edit_co(t_al *al, t_walls *walls)
{
	char					*tmp;

	ft_strdel(&al->text.x_start.str);
	ft_strdel(&al->text.y_start.str);
	ft_strdel(&al->text.x_end.str);
	ft_strdel(&al->text.y_end.str);
	tmp = ft_itoa(walls->x1 / 10);
	al->text.x_start.str = ft_strjoin("X1 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(walls->x2 / 10);
	al->text.x_end.str = ft_strjoin("X2 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(walls->y1 / 10);
	al->text.y_start.str = ft_strjoin("Y1 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(walls->y2 / 10);
	al->text.y_end.str = ft_strjoin("Y2 = ", tmp);
	ft_strdel(&tmp);
}

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
	// (al->sect->walls) ? assign_edit_co(al, index_wall(al)) : 0;
	(al->sect->walls) ? assign_edit_co(al, get_co_wal(al)) : 0;
	tmp = ft_itoa(al->edit.index_wall);
	ft_strdel(&al->text.wall_index.str);
	al->text.wall_index.str = ft_strjoin("Wall ", tmp);
	ft_strdel(&tmp);
}

void			interactive_arrow(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (al->sect)
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
		if (al->edit.index_wall < nb_wall(al))
			draw_triangle(itop(180, 69), 1, al->surf_ed, inr(itop(176, 58),
			itop(195, 88), itop(mev.x, mev.y)) ? BLACK : WHITE);
	}
}

void			editor(t_al *al)
{
	set_edit(al);
	set_edit_menu(al);
	if (al->sect)
		draw_sect(al, al->sect);
	interactive_arrow(al);
	refresh(al);
}
