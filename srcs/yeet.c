/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/30 11:34:44 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_wall(t_walls *walls)
{
	if (walls->next)
		free_wall(walls->next);
	free(walls);
	walls = NULL;
}

void	free_sect(t_sector *sect)
{
	if (sect->next)
		free_sect(sect->next);
	free_wall(sect->walls);
	free(sect);
	sect = NULL;
}

void	yeet(t_al *al)
{
	al->sect ? free_sect(al->sect) : 0;
	al->font ? TTF_CloseFont(al->font) : 0;
	al->ttf_st ? TTF_Quit() : 0;
	al->sdlsurf ? SDL_FreeSurface(al->sdlsurf) : 0;
	al->surf_ed ? SDL_FreeSurface(al->surf_ed) : 0;
	al->win_ed ? SDL_DestroyWindow(al->win_ed) : 0;
	al->ent ? ft_memdel((void**)&(al->ent)) : 0;
	al->rotent ? ft_memdel((void**)&(al->rotent)) : 0;
	free(al);
	exit(0);
}
