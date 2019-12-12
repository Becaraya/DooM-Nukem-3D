/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_edit_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:12:32 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/19 16:13:13 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		draw_wall(t_al *al, t_walls *wall)
{
	t_point		a;
	t_point		b;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	(wall->x1 != -1) ? ft_put_line(a, b, al->sdlsurf, WHITE) : 0;
	if (wall->next)
		draw_wall(al, wall->next);
}

void		draw_sect(t_al *al, t_sector *sect)
{
	if (sect->walls->x1 != -1)
		draw_wall(al, sect->walls);
	if (sect->next)
		draw_sect(al, sect->next);
}
