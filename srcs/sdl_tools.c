/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:09:36 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Color		add_color(int color)
{
	SDL_Color c;

	c.a = color >> 24;
	c.r = color >> 16;
	c.g = color >> 8;
	c.b = color;
	return (c);
}

SDL_Rect		get_rect(int x, int y)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	return (rect);
}
