/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/24 17:05:36 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// static void		print_wall(t_walls *wall)
// {
// 	if (wall->next)
// 		print_wall(wall->next);
// 	printf("x1 == %f\n", wall->x1);
// 	printf("y1 == %f\n", wall->y1);
// 	printf("x2 == %f\n", wall->x2);
// 	printf("y2 == %f\n\n", wall->y2);
// }

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
			j++;
			tmp_w = tmp_w->next;
		}
		tmp_s = tmp_s->next;
	}
}

void	set_default_player(t_al *al)
{
	al->g = DEFAULT_G;
	al->play.mass = PLAYER_MASS;
	al->play.power_mult = 1;
	al->play.size = PLAYER_SIZE;
	al->play.eyez = PLAYER_SIZE - PLAYER_EYE_TOP;
	al->play.alive = 10;
}

void	m_press_ed_glob_n_arr(t_al *al, SDL_MouseButtonEvent bev)
{
	arrow_stat(al, bev);
	mouse_press_edit_mini_menu(al, bev);
	mouse_press_edit_setting_sector(al, bev);
	mouse_press_edit_player(al, bev);
}

void	reset_map(t_al *al)
{
	free_sect(al->sect);
	al->sect = NULL;
	al->nb_sec = 0;
	al->edit.index_sect = 0;
	al->edit.index_wall = 0;
}

void	mouse_press_edit_menu(t_al *al, SDL_MouseButtonEvent bev)
{
// printf("x == %d // y == %d \n", bev.x, bev.y);
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
	else
		m_press_ed_glob_n_arr(al, bev);
	if (inr(itop(45, 125), itop(230, 170), itop(bev.x, bev.y)))
		al->diff = (al->diff == 0) ? 1 : 0;
	if (inr(itop(280, 125), itop(460, 170), itop(bev.x, bev.y))
		&& al->edit.stat != DRAWING && al->sect)
		reset_map(al);
	if (inr(itop(495, 125), itop(645, 170), itop(bev.x, bev.y)))
		set_default_player(al);
}

void	mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	if (bev.windowID == 1)
	{
		print_al(al);
		if (al->edit.stat == SELECT)
		{
			al->edit.stat = DRAWING;
			al->nb_sec++;
			al->edit.index_wall = 1;
			add_sector(al, itop(bev.x, bev.y));
		}
		else if (al->edit.stat == DRAWING)
			check_can_add(al, al->sect, itop(bev.x, bev.y));
	}
	if (bev.windowID == 2)
		mouse_press_edit_menu(al, bev);
}
