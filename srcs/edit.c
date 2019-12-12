/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 01:00:19 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <stdlib.h>
#define TEX_SIZE_MENU 100

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


void		assign_edit_co(t_al *al, t_walls *walls)
{
	char	*tmp;

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

t_walls		*get_co_wal(t_al *al)
{
	t_sector	*tmp_s;
	t_walls		*tmp_w;
	int			i;
	int			j;

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

void		print_co(t_al *al)
{
	char *tmp;

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

void		set_edit_menu(t_al *al)
{

	ft_memset(al->surf_ed->pixels, LIGHT_GREY, WIN_EDIT_SIZEX * WIN_EDIT_SIZEY * sizeof(int));
	if (al->sect)
	{
		print_co(al);
	}
	if (al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itop(590, 15), itop(699, 48), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(45, 240), itop(220, 285), itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_SECT)
		put_rectangle(al->surf_ed, itop(45, 240), itop(220, 285), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 240), itop(460, 285), itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_WALL)
		put_rectangle(al->surf_ed, itop(280, 240), itop(460, 285), BLACK);
	if ((al->ev.motion.windowID == 2 && (inr(itop(495, 460), itop(645, 500), itop(al->ev.motion.x, al->ev.motion.y)))) || al->edit.stat == SELECT || al->edit.stat == DRAWING)
		put_rectangle(al->surf_ed, itop(495, 460), itop(645, 500), BLACK);
	if ((al->ev.motion.windowID == 2 && inr(itop(280, 320), itop(460, 365), itop(al->ev.motion.x, al->ev.motion.y))) || al->edit.stat == EDIT_WALL)
		put_rectangle(al->surf_ed, itop(280, 320), itop(460, 365), BLACK);
}


void 	display_tex_menu(SDL_Surface *surf, t_tex tex, int i)
{
	unsigned int tex_x;
	unsigned int tex_y;
	int x;
	int y;

	y = i;
	tex_y = 0;
	while ((y != surf->h) && (tex_y < tex.size_y) && y < (i + TEX_SIZE_MENU))
	{
		x = surf->w - TEX_SIZE_MENU;
		tex_x = x / tex.size_x;
		while (x != surf->w && tex_x < tex.size_x)
		{
			((int *)surf->pixels)[x + y * surf->w] = tex.pix[tex_x + tex_y * tex.size_x];
			tex_x++;
			x++;
		}
		tex_y++;
		y++;
	}

}

void 	click_on_menu(t_al *al, SDL_Surface *surf)
{
	if (al->ev.type == SDL_MOUSEBUTTONDOWN && al->ev.motion.windowID == 2)
	{
		if (al->ev.button.x >= surf->w - TEX_SIZE_MENU && al->ev.button.y <= al->nb_tex * TEX_SIZE_MENU)
		{
			al->tex_choice = al->ev.button.y / TEX_SIZE_MENU;
			// printf("tex = %d\n",al->tex_choice);
			// printf("mouse (%d,%d)\n",al->ev.button.x,al->ev.button.y);
			// printf("id = %d\n",al->ev.motion.windowID);
		}
	}
}

void tex_menu(t_al *al)
{
	SDL_Surface *surf;
	int i;

	// printf("nb tex = %d\n",al->nb_tex);
	surf = al->surf_ed;
	i = -1;
	while (++i != al->nb_tex)
	{
		display_tex_menu(surf,al->tex[i],(i * TEX_SIZE_MENU));
	}
	click_on_menu(al, surf);
}

void	interactive_arrow(t_al *al)
{
	SDL_MouseMotionEvent	mev;

	mev = al->ev.motion;
	if (al->sect)
	{
		if (al->edit.index_sect > 1)
			draw_triangle(itop(160, 30), -1, al->surf_ed, inr(itop(145, 15), itop(175, 47), itop(mev.x, mev.y)) ? BLACK : WHITE);
		if (al->edit.index_sect < al->nb_sec)
			draw_triangle(itop(180, 30), 1, al->surf_ed, inr(itop(176, 15), itop(195, 47), itop(mev.x, mev.y)) ? BLACK : WHITE);
		// if (al->sect->nb_wal > 0)
		// {
			// printf("%i\n", al->sect->nb_wal);
		if (al->edit.index_wall > 0)
			draw_triangle(itop(160, 69), -1, al->surf_ed, inr(itop(145, 58), itop(175, 88), itop(mev.x, mev.y)) ? BLACK : WHITE);
		if (al->edit.index_wall < nb_wall(al))
			draw_triangle(itop(180, 69), 1, al->surf_ed, inr(itop(176, 58), itop(195, 88), itop(mev.x, mev.y)) ? BLACK : WHITE);
		// }
	}
}

void	draw_interactive_buttons(t_al *al)
{
	interactive_arrow(al);
}

void	editor(t_al *al)
{
	set_edit(al);
	set_edit_menu(al);
	// tex_menu(al);
	if (al->sect)
		draw_sect(al, al->sect);

	refresh(al);
}
