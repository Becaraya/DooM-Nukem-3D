/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:52:57 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/04 14:51:42 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				display_tex_menu(SDL_Surface *surf, t_tex tex, int i)
{
	unsigned int	tex_x;
	unsigned int	tex_y;
	int				x;
	int				y;

	y = i;
	tex_y = 0;
	while ((y != surf->h) && (tex_y < tex.size_y) && y < (i + TEX_SIZE_MENU))
	{
		x = surf->w - TEX_SIZE_MENU;
		tex_x = x / tex.size_x;
		while (x != surf->w && tex_x < tex.size_x)
		{
			((int *)surf->pixels)[x + y * surf->w] =
				tex.pix[tex_x + tex_y * tex.size_x];
			tex_x++;
			x++;
		}
		tex_y++;
		y++;
	}
}

static void			set_wall_tex(t_al *al)
{
	t_sector		*tmp_s;
	t_walls			*tmp_w;
	int				i;
	unsigned int	j;

	i = 0;
	j = 0;
	tmp_s = al->sect;
	while (al->edit.index_sect + i++ < al->nb_sec)
		tmp_s = tmp_s->next;
	tmp_w = tmp_s->walls;
	while (j++ != al->edit.index_wall)
		tmp_w = tmp_w->next;
	tmp_w->wall_tex = al->tex_choice;
}

static void			set_flo_tex(t_al *al)
{
	t_sector		*tmp_s;
	int				i;

	i = 0;
	tmp_s = al->sect;
	while (al->edit.index_sect + i++ < al->nb_sec)
		tmp_s = tmp_s->next;
	tmp_s->fl_tex = al->tex_choice;
}

void				click_on_menu(t_al *al, SDL_Surface *surf)
{
	int				i;
	t_sector		*tmp_s;

	if (al->ev.type == SDL_MOUSEBUTTONDOWN && al->ev.motion.windowID == 2)
	{
		if (al->ev.button.x >= surf->w - TEX_SIZE_MENU
		&& al->ev.button.y <= (al->nb_tex + 1) * TEX_SIZE_MENU)
		{
			al->tex_choice = al->ev.button.y / TEX_SIZE_MENU;
			if (al->edit.stat == SET_WALL_TEXT)
				set_wall_tex(al);
			if (al->edit.stat == SET_FLO_TEXT)
				set_flo_tex(al);
			if (al->edit.stat == SET_CEL_TEXT)
			{
				i = 0;
				tmp_s = al->sect;
				while (al->edit.index_sect + i++ < al->nb_sec)
					tmp_s = tmp_s->next;
				tmp_s->ce_tex = al->tex_choice;
			}
			al->edit.stat = SELECT;
		}
	}
}

void				tex_menu(t_al *al)
{
	SDL_Surface		*surf;
	int				i;

	surf = al->surf_ed;
	i = -1;
	while (++i <= al->nb_tex)
	{
		display_tex_menu(surf, al->tex[i], (i * TEX_SIZE_MENU));
	}
	click_on_menu(al, surf);
}
