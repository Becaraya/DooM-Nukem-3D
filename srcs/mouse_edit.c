/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/24 12:08:01 by becaraya         ###   ########.fr       */
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
        al->wall->x2 = bev.x - (bev.x % al->edit.zoom);
        al->wall->y2 = bev.y - (bev.y % al->edit.zoom);
    }
    else
    {
        al->wall->x1 = bev.x - (bev.x % al->edit.zoom);
        al->wall->y1 = bev.y - (bev.y % al->edit.zoom);
    }
}

int				check_existance(t_wall *lst, t_wall *wall)
{
	if (lst->x1 == wall->x1 && lst->x2 == wall->x2 && lst->y1 == wall->y1 && lst->y2 == wall->y2)
		return (1);
	if (lst->x1 == wall->x2 && lst->x2 == wall->x1 && lst->y1 == wall->y2 && lst->y2 == wall->y1)
		return (1);
	if (wall->next)
		return(check_existance(lst, wall->next));
	return (0);
}

void     stat_draw(t_al *al, SDL_MouseButtonEvent bev, int type)
{
	set_coo(al, bev, 1);
	if (al->wall->next && check_existance(al->wall, al->wall->next) == 1)
		return ;
	new_wall(al);
	set_coo(al, bev, 2);
	al->wall->type = type;
	return ;
}

void		    mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	printf("____________________________________________________________\n");
	print_al(al->wall);
	if (bev.windowID == 1)
	{
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
}
