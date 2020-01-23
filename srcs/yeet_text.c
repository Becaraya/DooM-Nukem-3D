/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:36:45 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/22 23:54:41 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			ft_rectdel(SDL_Rect **re)
{
	ft_memdel((void **)re);
}

void			free_text_hei_num(t_al *al)
{
	al->text.ce_hei_num.str ? ft_strdel(&al->text.ce_hei_num.str) : 0;
	al->text.ce_hei_num.where ? ft_rectdel(&al->text.ce_hei_num.where) : 0;
	al->text.fl_hei_num.str ? ft_strdel(&al->text.fl_hei_num.str) : 0;
	al->text.fl_hei_num.where ? ft_rectdel(&al->text.fl_hei_num.where) : 0;
}

void			free_text_next_next(t_al *al)
{
	al->text.set_player.str ? ft_strdel(&al->text.set_player.str) : 0;
	al->text.set_player.where ? ft_rectdel(&al->text.set_player.where) : 0;
	al->text.life.str ? ft_strdel(&al->text.life.str) : 0;
	al->text.life.where ? ft_rectdel(&al->text.life.where) : 0;
	al->text.power.str ? ft_strdel(&al->text.power.str) : 0;
	al->text.power.where ? ft_rectdel(&al->text.power.where) : 0;
	al->text.weapon.str ? ft_strdel(&al->text.weapon.str) : 0;
	al->text.weapon.where ? ft_rectdel(&al->text.weapon.where) : 0;
	al->text.size.str ? ft_strdel(&al->text.size.str) : 0;
	al->text.size.where ? ft_rectdel(&al->text.size.where) : 0;
	al->text.mass.str ? ft_strdel(&al->text.mass.str) : 0;
	al->text.mass.where ? ft_rectdel(&al->text.mass.where) : 0;
	al->text.gravity.str ? ft_strdel(&al->text.gravity.str) : 0;
	al->text.gravity.where ? ft_rectdel(&al->text.gravity.where) : 0;
	al->text.is_door.str ? ft_strdel(&al->text.is_door.str) : 0;
	al->text.is_door.where ? ft_rectdel(&al->text.is_door.where) : 0;
}

void			free_text_next(t_al *al)
{
	al->text.sector.str ? ft_strdel(&al->text.sector.str) : 0;
	al->text.sector.where ? ft_rectdel(&al->text.sector.where) : 0;
	al->text.tools.str ? ft_strdel(&al->text.tools.str) : 0;
	al->text.tools.where ? ft_rectdel(&al->text.tools.where) : 0;
	al->text.set_spawn.str ? ft_strdel(&al->text.set_spawn.str) : 0;
	al->text.set_spawn.where ? ft_rectdel(&al->text.set_spawn.where) : 0;
	al->text.set_end.str ? ft_strdel(&al->text.set_end.str) : 0;
	al->text.set_end.where ? ft_rectdel(&al->text.set_end.where) : 0;
	al->text.set_bad_pig.str ? ft_strdel(&al->text.set_bad_pig.str) : 0;
	al->text.set_bad_pig.where ? ft_rectdel(&al->text.set_bad_pig.where) : 0;
	al->text.wall_tex.str ? ft_strdel(&al->text.wall_tex.str) : 0;
	al->text.wall_tex.where ? ft_rectdel(&al->text.wall_tex.where) : 0;
	al->text.fl_tex.str ? ft_strdel(&al->text.fl_tex.str) : 0;
	al->text.fl_tex.where ? ft_rectdel(&al->text.fl_tex.where) : 0;
	al->text.ce_tex.str ? ft_strdel(&al->text.ce_tex.str) : 0;
	al->text.ce_tex.where ? ft_rectdel(&al->text.ce_tex.where) : 0;
	al->text.fl_hei.str ? ft_strdel(&al->text.fl_hei.str) : 0;
	al->text.fl_hei.where ? ft_rectdel(&al->text.fl_hei.where) : 0;
	al->text.ce_hei.str ? ft_strdel(&al->text.ce_hei.str) : 0;
	al->text.ce_hei.where ? ft_rectdel(&al->text.ce_hei.where) : 0;
	al->text.draw.str ? ft_strdel(&al->text.draw.str) : 0;
	al->text.draw.where ? ft_rectdel(&al->text.draw.where) : 0;
	al->text.link.str ? ft_strdel(&al->text.link.str) : 0;
	al->text.link.where ? ft_rectdel(&al->text.link.where) : 0;
}

void			free_text(t_al *al)
{
	al->text.gen_map.str ? ft_strdel(&al->text.gen_map.str) : 0;
	al->text.gen_map.where ? ft_rectdel(&al->text.gen_map.where) : 0;
	al->text.sect_index.str ? ft_strdel(&al->text.sect_index.str) : 0;
	al->text.sect_index.where ? ft_rectdel(&al->text.sect_index.where) : 0;
	al->text.wall_index.str ? ft_strdel(&al->text.wall_index.str) : 0;
	al->text.wall_index.where ? ft_rectdel(&al->text.wall_index.where) : 0;
	al->text.settings.str ? ft_strdel(&al->text.cancel.str) : 0;
	al->text.settings.where ? ft_rectdel(&al->text.cancel.where) : 0;
	al->text.wall.str ? ft_strdel(&al->text.wall.str) : 0;
	al->text.wall.where ? ft_rectdel(&al->text.wall.where) : 0;
	al->text.reset_map.str ? ft_strdel(&al->text.reset_map.str) : 0;
	al->text.reset_map.where ? ft_rectdel(&al->text.reset_map.where) : 0;
	al->text.reset_player.str ? ft_strdel(&al->text.reset_player.str) : 0;
	al->text.reset_player.where ? ft_rectdel(&al->text.reset_player.where) : 0;
	free_text_hei_num(al);
	free_text_next(al);
	free_text_next_next(al);
}
