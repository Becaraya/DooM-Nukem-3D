/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texte.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:51:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/13 21:34:29 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_text_edit(t_al *al)
{
	set_text(&al->text.sect_index, "WHO", get_rect(25, 20),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall_index, "WHO WALL", get_rect(25, 58),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.x_start, "X1", get_rect(25, 100),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.y_start, "Y1", get_rect(150, 100),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.x_end, "X2", get_rect(25, 150),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.y_end, "Y2", get_rect(150, 150),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.cancel, "CANCEL", get_rect(600, 20),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.settings, "Settings", get_rect(25, 200),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.sector, "Sector", get_rect(70, 250),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.fl_tex, "Floor Texture", get_rect(70, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.fl_hei, "Floor Height", get_rect(70, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.ce_tex, "Ceiling Texture", get_rect(300, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	init_text_edit_next(al);
}

void	init_text_edit_next(t_al *al)
{
	set_text(&al->text.ce_hei, "Ceiling Height", get_rect(300, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall, "Wall", get_rect(300, 250),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall_tex, "Wall Texture", get_rect(70, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.tools, "Tools", get_rect(25, 500),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.set_spawn, "Set Spawn", get_rect(70, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.set_bad_pig, "Set Goret", get_rect(300, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.draw, "Draw", get_rect(520, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.link, "Sector Link", get_rect(70, 615),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.gen_map, "GENERATION MAP", get_rect(295, 665),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
}
