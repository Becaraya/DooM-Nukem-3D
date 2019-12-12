/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 01:04:05 by becaraya         ###   ########.fr       */
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

void			init_sect(t_al *al, t_sector *sect)
{
	t_sector	*new;

	new = NULL;
	if (!sect)
	{
		if (!(al->sect = ft_memalloc(sizeof(t_sector))))
			yeet(al);
		ft_bzero(al->sect, sizeof(t_sector *));
		if (!(al->sect->walls = (t_walls *)ft_memalloc(sizeof(t_walls))))
			yeet(al);
		ft_bzero(al->sect->walls, sizeof(t_walls *));
		set_coo(al, itop(-1, -1), 1, al->sect->walls);
		set_coo(al, itop(-1, -1), 2, al->sect->walls);
		al->sect->next = NULL;
		al->sect->walls->next = NULL;
	}
	else
	{
		if (!(new = ft_memalloc(sizeof(t_sector))))
			yeet(al);
		if (!(new->walls = ft_memalloc(sizeof(t_walls))))
			yeet(al);
		set_coo(al, itop(-1, -1), 1, new->walls);
		set_coo(al, itop(-1, -1), 2, new->walls);
		new->next = al->sect;
		al->sect = new;
	}
	al->sect->nb_wal = 0;
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
	if (!(new = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	new->x1 = sect->walls->x2;
	new->y1 = sect->walls->y2;
	new->x2 = sect->walls->x2;
	new->y2 = sect->walls->y2;
	new->next = sect->walls;
	sect->walls = new;
	if (check_end_sector(sect->walls->next, coo.x - (coo.x % al->edit.zoom),
		coo.y - (coo.y % al->edit.zoom)) == 1)
		al->edit.stat = SELECT;
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

static void		print_al(t_al *al) // a tej plus tard
{
	t_sector	*tmp_s;
	t_walls		*tmp_w;
	int i = 0;
	int j = 0;

	tmp_s = al->sect;
	while (tmp_s)
	{
		printf("\nSECTOR %d\n", al->nb_sec - i);
		tmp_w = tmp_s->walls;
		j = 0;
		i++;
		printf("                       tmp_s->nb_wall = %d\n", tmp_s->nb_wal);
		while (tmp_w)
		{
			printf("WALL %d // x1 = %f // x2 = %f // y1 = %f // y2 = %f\n", tmp_s->nb_wal - j, tmp_w->x1, tmp_w->x2, tmp_w->y1, tmp_w->y2);
			// printf("wall x1 = %d // wall x1 = %d // wall x1 = %d // wall x1 = %d\n")
			j++;
			tmp_w = tmp_w->next;
		}
		tmp_s = tmp_s->next;
	}
}

void			check_can_add(t_al *al, t_sector *sect, t_point coo)
{
	t_point tmp;

	tmp.x = coo.x - (coo.x % al->edit.zoom);
	tmp.y = coo.y - (coo.y % al->edit.zoom);
	if (sect->walls->next && sect->walls->next->x1 == tmp.x
		&& sect->walls->next->y1 == tmp.y)
		return ;
	add_wall(al, al->sect, coo);

}

void			delonesect(t_sector **sect)
{
	t_sector *tmp;

	tmp = NULL;
	if (!(*sect)->next)
		ft_memdel((void **)sect);
	else
	{
		tmp = (*sect)->next;
		free(*sect);
		*sect = tmp;
	}
}

void			mouse_press_edit_menu(t_al *al, SDL_MouseButtonEvent bev)
{
		printf("x == %d // y == %d \n", bev.x, bev.y);
	if (al->edit.stat == DRAWING)
	{
		if (bev.x > 590 && bev.x < 685 && bev.y > 15 && bev.y < 48)
		{
			al->edit.stat = SELECT;
			free_wall(al->sect->walls);
			al->nb_sec--;
			delonesect(&al->sect);
		}
	}
	// if (al->edit.stat >= EDIT_WALL || al->edit.stat == SELECT)
	// {
	// 	if (inr())
	// }
	if (al->sect)
	{
		if (al->edit.index_sect > 1 && bev.x > 145 && bev.x < 175 && bev.y > 15 && bev.y < 47)
		{
			!(al->edit.index_wall = 0) ? al->edit.index_sect-- : 0;
			(al->edit.stat != DRAWING) ? al->edit.stat = SELECT : 0;
		}
		if (al->edit.index_sect < al->nb_sec && bev.x > 176 && bev.x < 195 && bev.y > 15 && bev.y < 47)
		{	
			!(al->edit.index_wall = 0) ? al->edit.index_sect++ : 0;
			(al->edit.stat != DRAWING) ? al->edit.stat = SELECT : 0;
		}
		if (al->edit.index_wall > 0 && bev.x > 145 && bev.x < 175 && bev.y > 59 && bev.y < 86)
			al->edit.index_wall--;
		if (al->edit.index_wall < nb_wall(al)
			&& bev.x > 176 && bev.x < 195 && bev.y > 59 && bev.y < 86)
			al->edit.index_wall++;
	}
}

void		    mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	// printf("____________________________________________________________\n");
	// (al->sect) ? print_al(al) : 0; ///////////////////////////////////////////// c est a tej quand tous seras finis
	if (bev.windowID == 1)
	{
		if (al->edit.stat == SELECT)
		{
			al->edit.stat = DRAWING;
			al->nb_sec++;
			add_sector(al, itop(bev.x, bev.y));
		}
		if (al->edit.stat == DRAWING)
			check_can_add(al, al->sect, itop(bev.x, bev.y));
	}
	if (bev.windowID == 2)
		mouse_press_edit_menu(al, bev);
}
