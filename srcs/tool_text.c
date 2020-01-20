/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:53:55 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/17 16:22:54 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			init_ttf(t_al *al)
{
	(!TTF_Init()) ? al->ttf_st = 1 : yeet(al);
	if (!(al->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		yeet(al);
}

int				set_text(t_text *text, char *str, SDL_Rect coo, SDL_Color clr)
{
	if (!(text->str = ft_strdup(str)))
		return (-1);
	if (!(text->where = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect))))
		return (-1);
	text->where->x = coo.x;
	text->where->y = coo.y;
	ft_memcpy(&text->clr, &clr, sizeof(&clr));
	return (0);
}

int				titlecmp(t_al *al, t_text text)
{
	if (!ft_strcmp(text.str, al->text.settings.str)
		&& cocmp(text.where, al->text.settings.where))
		return (1);
	if (!ft_strcmp(text.str, al->text.cancel.str)
		&& cocmp(text.where, al->text.cancel.where))
		return (1);
	if (!ft_strcmp(text.str, al->text.tools.str)
		&& cocmp(text.where, al->text.tools.where))
		return (1);
	return (0);
}
