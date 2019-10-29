/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/29 14:56:52 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void     set_coo(t_al *al, t_point bev, int who, t_walls *wall)
{
    if (who == 1)
    {
        wall->x1 = bev.x - (bev.x % al->edit.zoom);
        wall->y1 = bev.y - (bev.y % al->edit.zoom);
    }
    else
    {
        wall->x2 = bev.x - (bev.x % al->edit.zoom);
        wall->y2 = bev.y - (bev.y % al->edit.zoom);
    }
}

t_point			itopoint(int x, int y) //se prononce "I TAU POINT"
{
	t_point		res;

	res.x = x;
	res.y = y;
	return (res);
}

void			init_sect(t_al *al, t_sector *sect)
{
	t_sector	*new;

	new = NULL;
	if (!sect)
	{
		if (!(al->sect = (t_sector *)ft_memalloc(sizeof(t_sector))))
			yeet(al);
		if (!(al->sect->walls = (t_walls *)ft_memalloc(sizeof(t_walls))))
			yeet(al);
		set_coo(al, itopoint(-1, -1), 1, al->sect->walls);
		set_coo(al, itopoint(-1, -1), 2, al->sect->walls);
		al->sect->next = NULL;
		al->sect->walls->next = NULL;
	}
	else
	{
		if (!(new = (t_sector *)ft_memalloc(sizeof(t_sector))))
			yeet(al);
		if (!(new->walls = (t_walls *)ft_memalloc(sizeof(t_walls))))
			yeet(al);
		set_coo(al, itopoint(-1, -1), 1, new->walls);
		set_coo(al, itopoint(-1, -1), 2, new->walls);
		new->next = al->sect;
		al->sect = new;
	}
}

void			add_sector(t_al *al, t_point coo)
{
	init_sect(al, al->sect);
	set_coo(al, coo, 1, al->sect->walls);
	set_coo(al, coo, 2, al->sect->walls);
}

int				check_end_sector(t_walls *wall, int x, int y)
{
	t_walls *tmp;

	tmp = wall;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->x1 == x && tmp->y1 == y)
		return (1);
	return (0);
}

void			add_wall(t_al *al, t_sector *sect, t_point coo)
{
	t_walls          	*new;
	
	if (sect->walls->x1 == sect->walls->x2 && sect->walls->y1 == sect->walls->y2)
		return ;
	if (!(new = (t_walls *)ft_memalloc(sizeof(t_walls))))
		yeet(al);
	
	new->x1 = sect->walls->x2;
	new->y1 = sect->walls->y2;
	new->x2 = sect->walls->x2;
	new->y2 = sect->walls->y2;
	new->next = sect->walls;
	sect->walls = new;
	if (check_end_sector(sect->walls->next, coo.x - (coo.x % al->edit.zoom),
		coo.y - (coo.y % al->edit.zoom)) == 1)
		al->edit.stat = FIRST_CLICK;
}

static void		print_wall(t_walls *wall)
{
	if (wall->next)
		print_wall(wall->next);
	printf("x1 == %f\n", wall->x1);
	printf("y1 == %f\n", wall->y1);
	printf("x2 == %f\n", wall->x2);
	printf("y2 == %f\n\n", wall->y2);
}

static void		print_al(t_sector *sect)
{
	printf("_________________SECTOR_____________________________________\n");
	if (sect)
	{
		if (sect->next)
			print_al(sect->next);
		print_wall(sect->walls);
	}
}

void		    mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	printf("____________________________________________________________\n");
	(al->sect) ? print_al(al->sect) : 0;
	if (bev.windowID == 1)
	{
		if (al->edit.stat == FIRST_CLICK)
		{
			al->edit.stat = DRAWING;
			add_sector(al, itopoint(bev.x, bev.y));
			// printf("test seg\n");
		}
		if (al->edit.stat == DRAWING)
			add_wall(al, al->sect, itopoint(bev.x, bev.y));
			// stat_draw(al, bev, SIMPLE);
	}
	// if (bev.windowID == 2)
	// 	mouse_press_edit_menu(al);
}
