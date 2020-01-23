/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texte.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:51:16 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/22 11:14:10 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_text_edit(t_al *al)
{
	set_text(&al->text.sect_index, "WHO", get_rect(25, 20),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall_index, "WHO WALL", get_rect(25, 58),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.dif_ez, "Difficulty : Easy", get_rect(70, 135),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.dif_ha, "Difficulty : Hard", get_rect(70, 135),
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

void	init_text_edit_next_next(t_al *al)
{
	set_text(&al->text.set_player, "Player", get_rect(520, 250),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.life, "Life", get_rect(70, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.power, "Power", get_rect(300, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.weapon, "Weapon", get_rect(520, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.size, "Size", get_rect(70, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.mass, "Mass", get_rect(300, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.player_value, "Player num", get_rect(570, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.reset_map, "Reset Map", get_rect(300, 135),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.reset_player, "Reset Player", get_rect(515, 135),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.gravity, "Gravity", get_rect(300, 615),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.g_num, "9.81", get_rect(570, 625),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.is_door, "Is Door", get_rect(520, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
}

void	init_text_edit_next(t_al *al)
{
	set_text(&al->text.ce_hei, "Ceiling Height", get_rect(300, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.ce_hei_num, "Ceilinh Hei Num", get_rect(570, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.fl_hei_num, "Floor Hei Num", get_rect(570, 410),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall, "Wall", get_rect(300, 250),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.wall_tex, "Wall Texture", get_rect(70, 330),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.tools, "Tools", get_rect(25, 500),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.set_spawn, "Set Spawn", get_rect(70, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.set_end, "Set End", get_rect(70, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.set_bad_pig, "Set Goret", get_rect(300, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.draw, "Draw", get_rect(520, 550),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.link, "Sector Link", get_rect(70, 615),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	set_text(&al->text.gen_map, "GENERATION MAP", get_rect(295, 665),
	add_color(TEXT_EDITOR)) == -1 ? yeet(al) : 0;
	init_text_edit_next_next(al);
}
