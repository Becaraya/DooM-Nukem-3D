/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/12 16:02:12 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <stdlib.h>

static void		set_edit(t_al *al)
{
	int			x;
	int 		y;
	/* si tu veut init une grosse zone a null utilise bzero plutot  que des for
	ou while. Et fait des typedef sur la win_size plutot que hardcode les val */
	x = 0;
	y = 0;
	ft_bzero(al->pix, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	// ft_memset(al->sdlsurf->pixels, WHITE, WIN_SIZEX * WIN_SIZEY * sizeof(int));
	
	while (x < WIN_SIZEX)
	{
		while (y < WIN_SIZEY)
		{
			if (((x % (al->edit.zoom)) == 0) && (y % (al->edit.zoom) == 0) && y > 0 && x > 0)
				al->pix[x + (y * WIN_SIZEX)] = WHITE;
			y++;
		}
		y = 0;
		x++;
	}
}

void			ft_put_line(t_point a, t_point b, SDL_Surface *surf, int color)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			tab[2];

	delta.x = ft_abs(b.x - a.x);
	delta.y = ft_abs(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	tab[0] = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		((int *)surf->pixels)[cur.x + cur.y * surf->w] = color;
		if ((tab[1] = tab[0] * 2) > -delta.y)
		{
			tab[0] -= delta.y;
			cur.x += sign.x;
		}
		if (tab[1] < delta.x)
		{
			tab[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void		draw_wall(t_al *al, t_walls *wall)
{
	t_point		a;
	t_point		b;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	(wall->x1 != -1) ? ft_put_line(a, b, al->sdlsurf, WHITE) : 0;
	if (wall->next)
		draw_wall(al, wall->next);
}

void		draw_sect(t_al *al, t_sector *sect)
{
	if (sect->walls->x1 != -1)
		draw_wall(al, sect->walls);
	if (sect->next)
		draw_sect(al, sect->next);
}

void		assign_edit_co(t_al *al)
{
	char *tmp;

	ft_strdel(&al->text.x_start.str);
	ft_strdel(&al->text.y_start.str);
	ft_strdel(&al->text.x_end.str);
	ft_strdel(&al->text.y_end.str);
	tmp = ft_itoa(al->sect->walls->x1);
	al->text.x_start.str = ft_strjoin("X1 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(al->sect->walls->x2);
	al->text.x_end.str = ft_strjoin("X2 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(al->sect->walls->y1);
	al->text.y_start.str = ft_strjoin("Y1 = ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(al->sect->walls->y2);
	al->text.y_end.str = ft_strjoin("Y2 = ", tmp);
	ft_strdel(&tmp);
}

void		put_rectangle(SDL_Surface *surf, t_point a, t_point b, int clr)
{
	t_point	c;
	t_point	d;

	c.x = a.x;
	c.y = b.y;
	d.x = b.x;
	d.y = a.y;
	ft_put_line(a, d, surf, clr);
	ft_put_line(a, c, surf, clr);
	ft_put_line(d, b, surf, clr);
	ft_put_line(b, c, surf, clr);
}

void		set_edit_menu(t_al *al)
{
	char *tmp;
	int i;

	i = 0;
	ft_memset(al->surf_ed->pixels, LIGHT_GREY, WIN_EDIT_SIZEX * WIN_EDIT_SIZEY * sizeof(int));
	if (al->nb_sect && al->sect)
	{
		tmp = ft_itoa(al->nb_sect);
		ft_strdel(&al->text.sect_para.str);
		al->text.sect_para.str = ft_strjoin("Sector ", tmp);
		ft_strdel(&tmp);
		if (al->sect->walls)
			assign_edit_co(al);
	}
	if (al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itopoint(590, 15), itopoint(685, 48), BLACK);
}

void	editor(t_al *al)
{
	set_edit(al);
	set_edit_menu(al);
	if (al->nb_sect && al->sect)
		draw_sect(al, al->sect);
	refresh(al);
}
