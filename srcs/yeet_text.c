/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:36:45 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/13 21:33:36 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		ft_rectdel(SDL_Rect **re)
{
	ft_memdel((void **)re);
}

void			free_text_next(t_al *al)
{
	al->text.sector.str ? ft_strdel(&al->text.sector.str) : 0;
	al->text.sector.where ? ft_rectdel(&al->text.sector.where) : 0;
	al->text.tools.str ? ft_strdel(&al->text.tools.str) : 0;
	al->text.tools.where ? ft_rectdel(&al->text.tools.where) : 0;
	al->text.set_spawn.str ? ft_strdel(&al->text.set_spawn.str) : 0;
	al->text.set_spawn.where ? ft_rectdel(&al->text.set_spawn.where) : 0;
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
	al->text.x_start.str ? ft_strdel(&al->text.x_start.str) : 0;
	al->text.x_start.where ? ft_rectdel(&al->text.x_start.where) : 0;
	al->text.y_start.str ? ft_strdel(&al->text.y_start.str) : 0;
	al->text.y_start.where ? ft_rectdel(&al->text.y_start.where) : 0;
	al->text.x_end.str ? ft_strdel(&al->text.x_end.str) : 0;
	al->text.x_end.where ? ft_rectdel(&al->text.x_end.where) : 0;
	al->text.y_end.str ? ft_strdel(&al->text.y_end.str) : 0;
	al->text.y_end.where ? ft_rectdel(&al->text.y_end.where) : 0;
	al->text.y_end.str ? ft_strdel(&al->text.cancel.str) : 0;
	al->text.y_end.where ? ft_rectdel(&al->text.cancel.where) : 0;
	al->text.settings.str ? ft_strdel(&al->text.cancel.str) : 0;
	al->text.settings.where ? ft_rectdel(&al->text.cancel.where) : 0;
	al->text.wall.str ? ft_strdel(&al->text.wall.str) : 0;
	al->text.wall.where ? ft_rectdel(&al->text.wall.where) : 0;
	free_text_next(al);
}
