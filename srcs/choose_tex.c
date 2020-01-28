/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:52:57 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 11:30:14 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		display_tex_menu(SDL_Surface *surf, t_tex tex, int i)
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

void		click_on_menu(t_al *al, SDL_Surface *surf)
{
	if (al->ev.type == SDL_MOUSEBUTTONDOWN && al->ev.motion.windowID == 2)
	{
		if (al->ev.button.x >= surf->w - TEX_SIZE_MENU
		&& al->ev.button.y <= al->nb_tex * TEX_SIZE_MENU)
		{
			al->tex_choice = al->ev.button.y / TEX_SIZE_MENU;
		}
	}
}

void		tex_menu(t_al *al)
{
	SDL_Surface		*surf;
	int				i;

	surf = al->surf_ed;
	i = -1;
	while (++i != al->nb_tex)
	{
		display_tex_menu(surf, al->tex[i], (i * TEX_SIZE_MENU));
	}
	click_on_menu(al, surf);
}
