/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:15:33 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/06 14:49:05 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	print_text(t_al *al, t_text text, SDL_Surface *surf)
{
	SDL_Surface		*tmp;
	int				title;

	tmp = NULL;
	title = 0;
	if (al->status == EDIT && (title = titlecmp(al, text)) == 1)
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

void	text_sect(t_al *al)
{
	if (al->edit.stat == EDIT_SECT || al->edit.stat == SET_FLO_TEXT
	|| al->edit.stat == SET_FLO_HEI
	|| al->edit.stat == SET_CEL_TEXT || al->edit.stat == SET_CEL_HEI)
	{
		if (al->edit.stat == SET_CEL_HEI)
			print_text(al, al->text.ce_hei_num, al->surf_ed);
		if (al->edit.stat == SET_FLO_HEI)
			print_text(al, al->text.fl_hei_num, al->surf_ed);
		print_text(al, al->text.fl_tex, al->surf_ed);
		print_text(al, al->text.ce_tex, al->surf_ed);
		print_text(al, al->text.fl_hei, al->surf_ed);
		print_text(al, al->text.ce_hei, al->surf_ed);
		print_text(al, al->text.is_door, al->surf_ed);
	}
	print_text(al, al->text.sect_index, al->surf_ed);
}

void	set_player_text(t_al *al)
{
	if (al->edit.stat >= SET_PLAYER && al->edit.stat <= MASS)
	{
		print_text(al, al->text.life, al->surf_ed);
		print_text(al, al->text.power, al->surf_ed);
		print_text(al, al->text.weapon, al->surf_ed);
		print_text(al, al->text.size, al->surf_ed);
		print_text(al, al->text.mass, al->surf_ed);
		if (al->edit.stat != SET_PLAYER)
			print_text(al, al->text.player_value, al->surf_ed);
	}
}

void	text_default_edit(t_al *al)
{
	print_text(al, al->text.gen_map, al->surf_ed);
	print_text(al, al->text.draw, al->surf_ed);
	print_text(al, al->text.sector, al->surf_ed);
	print_text(al, al->text.wall, al->surf_ed);
	print_text(al, al->text.set_player, al->surf_ed);
	print_text(al, al->text.tools, al->surf_ed);
	print_text(al, al->text.settings, al->surf_ed);
	print_text(al, al->text.reset_map, al->surf_ed);
	print_text(al, al->text.reset_player, al->surf_ed);
	set_player_text(al);
}

void	text(t_al *al)
{
	text_default_edit(al);
	if (al->hard == 0)
		print_text(al, al->text.dif_ez, al->surf_ed);
	else
		print_text(al, al->text.dif_ha, al->surf_ed);
	al->edit.stat == DRAWING ? print_text(al, al->text.cancel, al->surf_ed) : 0;
	if (al->sect)
	{
		text_sect(al);
		if (al->sect->walls)
		{
			if (al->edit.stat == EDIT_WALL || al->edit.stat == SET_WALL_TEXT)
				print_text(al, al->text.wall_tex, al->surf_ed);
			if (al->edit.stat == SET_END)
				print_text(al, al->text.set_end, al->surf_ed);
			else
				print_text(al, al->text.set_spawn, al->surf_ed);
			print_text(al, al->text.gravity, al->surf_ed);
			if (al->edit.stat == GRAVITY)
				print_text(al, al->text.g_num, al->surf_ed);
			print_text(al, al->text.set_bad_pig, al->surf_ed);
			print_text(al, al->text.link, al->surf_ed);
			print_text(al, al->text.wall_index, al->surf_ed);
		}
	}
}
