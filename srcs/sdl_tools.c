/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:09:36 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/12 15:59:47 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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
