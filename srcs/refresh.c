/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:15:33 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 23:27:05 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	print_text(t_al *al, t_text text, SDL_Surface *surf)
{
	SDL_Surface		*tmp;
	int				title;

	tmp = NULL;
	title = 0;
	if ((title = titlecmp(al, text)) == 1)
		TTF_SetFontStyle(al->font, TTF_STYLE_BOLD);
	if (!(tmp = TTF_RenderText_Blended(al->font, text.str, text.clr)))
		yeet(al);
	if (SDL_BlitSurface(tmp, 0, surf, text.where))
		yeet(al);
	else
		SDL_FreeSurface(tmp);
	if (title)
		TTF_SetFontStyle(al->font, TTF_STYLE_NORMAL);
}

void	text_edit_base(t_al *al)
{
	print_text(al, al->text.gen_map, al->surf_ed);
	print_text(al, al->text.draw, al->surf_ed);
	print_text(al, al->text.sector, al->surf_ed);
	print_text(al, al->text.wall, al->surf_ed);
	print_text(al, al->text.tools, al->surf_ed);
	print_text(al, al->text.settings, al->surf_ed);
}

void	text_edit_if_sect(t_al *al)
{
	if (al->edit.stat <= DRAWING || al->edit.stat == EDIT_SECT)
	{
		print_text(al, al->text.fl_tex, al->surf_ed);
		print_text(al, al->text.ce_tex, al->surf_ed);
		print_text(al, al->text.fl_hei, al->surf_ed);
		print_text(al, al->text.ce_hei, al->surf_ed);
	}
	print_text(al, al->text.x_start, al->surf_ed);
	print_text(al, al->text.y_start, al->surf_ed);
	print_text(al, al->text.x_end, al->surf_ed);
	print_text(al, al->text.sect_index, al->surf_ed);
	print_text(al, al->text.y_end, al->surf_ed);
	if (al->sect->walls)
	{
		if (al->edit.stat == EDIT_WALL)
			print_text(al, al->text.wall_tex, al->surf_ed);
		print_text(al, al->text.set_spawn, al->surf_ed);
		print_text(al, al->text.set_bad_pig, al->surf_ed);
		print_text(al, al->text.wall_index, al->surf_ed);
		print_text(al, al->text.link, al->surf_ed);
	}
}

void	text_edit(t_al *al)
{
	text_edit_base(al);
	if (al->edit.stat == DRAWING)
		print_text(al, al->text.cancel, al->surf_ed);
	if (al->sect)
		text_edit_if_sect(al);
}

void	refresh(t_al *al)
{
	if (al->status == EDIT)
		text_edit(al);
	if (SDL_UpdateWindowSurface(al->sdlwin))
		yeet(al);
	if (al->status == EDIT && (SDL_UpdateWindowSurface(al->win_ed)))
		yeet(al);
}
