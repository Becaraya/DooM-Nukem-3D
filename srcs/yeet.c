/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/11/12 15:59:53 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	ft_rectdel(SDL_Rect **re)
{
	ft_memdel((void **)re);
}

void	free_text(t_al *al)
{
	al->text.gen_map.str ? ft_strdel(&al->text.gen_map.str) : 0;
	al->text.gen_map.where ? ft_rectdel(&al->text.gen_map.where) : 0;
	al->text.sect_para.str ? ft_strdel(&al->text.sect_para.str) : 0;
	al->text.sect_para.where ? ft_rectdel(&al->text.sect_para.where) : 0;
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
}

void	free_wall(t_walls *walls)
{
	if (walls->next)
		free_wall(walls->next);
	ft_memdel(&walls);
}

void	free_sect(t_sector *sect)
{
	if (sect->next)
		free_sect(sect->next);
	free_wall(sect->walls);
	ft_memdel(&sect);
}

void	yeet(t_al *al)
{
	free_text(al);
	al->sect ? free_sect(al->sect) : 0;
	al->font ? TTF_CloseFont(al->font) : 0;
	al->ttf_st ? TTF_Quit() : 0;
	al->sdlsurf ? SDL_FreeSurface(al->sdlsurf) : 0;
	al->surf_ed ? SDL_FreeSurface(al->surf_ed) : 0;
	al->win_ed ? SDL_DestroyWindow(al->win_ed) : 0;
	if (al->sdlwin)
	{
		//SDL_DestroyWindow(al->sdlwin); // fais un ROOT LEAK, ô saint becaraya
		//SDL_Quit();					// eclaire nous de ta brillance
	}
	exit(0);
}
