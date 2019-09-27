/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/27 17:38:54 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		new_wall(t_al *al)
{
	t_wall          	*new;
	
	if (al->wall->x1 == al->wall->x2 && al->wall->y1 == al->wall->y2)
		return ;
	if (!(new = (t_wall *)ft_memalloc(sizeof(t_wall))))
		yeet(al);
	
	new->x1 = al->wall->x2;
	new->y1 = al->wall->y2;
	new->x2 = al->wall->x2;
	new->y2 = al->wall->y2;
	new->next = al->wall;
	al->wall->prev = new;
	al->wall = new;
}

static void		print_al(t_wall *wall)
{
	if (wall->next)
		print_al(wall->next);
	printf("x1 == %d\n", wall->x1);
	printf("y1 == %d\n", wall->y1);
	printf("x2 == %d\n", wall->x2);
	printf("y2 == %d\n\n", wall->y2);
}

static void     set_coo(t_al *al, SDL_MouseButtonEvent bev, int first)
{
    if (first == 1)
    {
        al->wall->x1 = bev.x - (bev.x % al->edit.zoom);
        al->wall->y1 = bev.y - (bev.y % al->edit.zoom);
    }
    else
    {
        al->wall->x2 = bev.x - (bev.x % al->edit.zoom);
        al->wall->y2 = bev.y - (bev.y % al->edit.zoom);
    }
}

static void     stat_draw(t_al *al, SDL_MouseButtonEvent bev, int type)
{
	set_coo(al, bev, 2);
	new_wall(al);
	set_coo(al, bev, 1);
	al->wall->type = type;
}

void		    mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	printf("____________________________________________________________\n");
	print_al(al->wall);
	if (al->edit.stat == FIRST_CLICK || al->edit.stat == RECTANGLE_SELECT)
	{
		al->edit.stat = (al->edit.stat == FIRST_CLICK) ? DRAWING
			: RECTANGLE_DRAW;
		set_coo(al, bev, 1);
		set_coo(al, bev, 2);
		
	}
	if (al->edit.stat == DRAWING)
		stat_draw(al, bev, SIMPLE);
	if (al->edit.stat == RECTANGLE_DRAW)
		stat_draw(al, bev, RECT);
}
