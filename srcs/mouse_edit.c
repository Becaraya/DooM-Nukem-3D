/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:53:16 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/20 19:07:03 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*static void		print_wall(t_walls *wall)
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
			printf("WALL %d // x1 = %f // x2 = %f // y1 = %f
				// y2 = %f\n", tmp_s->nb_wal - j, tmp_w->x1,
				tmp_w->x2, tmp_w->y1, tmp_w->y2);
			j++;
			tmp_w = tmp_w->next;
		}
		tmp_s = tmp_s->next;
	}
}*/

void			arrow_stat_hei(t_al *al, SDL_MouseButtonEvent bev)
{
	t_sector	*tmp;
	int			i;

	i = al->edit.index_sect - 1;
	tmp = al->sect;
	while (i--)
		tmp = tmp->next;
	if (al->edit.stat == SET_CEL_HEI)
	{
		if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435 && tmp->ce_hei > tmp->fl_hei && tmp->ce_hei)
			tmp->ce_hei -= 0.25;
		if (inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y)))
			tmp->ce_hei += 0.25;
	}
	if (al->edit.stat == SET_FLO_HEI)
	{
		if (bev.x > 520 && bev.x < 545 && bev.y > 410 && bev.y < 435 &&tmp->fl_hei > 0)
			tmp->fl_hei -= 0.25;
		if (inr(itop(630, 410), itop(660, 435), itop(bev.x, bev.y)) &&  tmp->ce_hei > tmp->fl_hei)
			tmp->fl_hei += 0.25;
	}
}

void			arrow_stat(t_al *al, SDL_MouseButtonEvent bev)
{
	if (al->edit.index_sect > 1 && bev.x > 145 && bev.x < 175
		&& bev.y > 15 && bev.y < 47)
	{
		!(al->edit.index_wall = 0) ? al->edit.index_sect-- : 0;
		al->edit.stat = SELECT;
	}
	if (al->edit.index_sect < al->nb_sec && bev.x > 176 && bev.x < 195
		&& bev.y > 15 && bev.y < 47)
	{
		!(al->edit.index_wall = 0) ? al->edit.index_sect++ : 0;
		al->edit.stat = SELECT;
	}
	if (al->edit.index_wall > 0 && bev.x > 145 && bev.x < 175
		&& bev.y > 59 && bev.y < 86)
		al->edit.index_wall--;
	if (al->edit.index_wall < nb_wall(al) - 1
		&& bev.x > 176 && bev.x < 195 && bev.y > 59 && bev.y < 86)
		al->edit.index_wall++;
	if (al->edit.stat == SET_CEL_HEI || al->edit.stat == SET_FLO_HEI)
		arrow_stat_hei(al, bev);
}

void			mouse_press_edit_mini_menu(t_al *al, SDL_MouseButtonEvent bev)
{
	if (inr(itop(495, 540), itop(645, 585),	itop(bev.x, bev.y)))
		al->edit.stat = SELECT;
	if (inr(itop(45, 605), itop(220, 650), itop(bev.x, bev.y)))
		al->edit.stat = LINK_MOD;
	if (inr(itop(45, 540), itop(220, 585), itop(bev.x, bev.y)))
		al->edit.stat = SET_SPAWN;
	if (inr(itop(280, 540), itop(460, 585), itop(bev.x, bev.y)))
		al->edit.stat = SET_BAD_PIG;
	if (inr(itop(45, 240), itop(220, 285), itop(bev.x, bev.y)))
		al->edit.stat = EDIT_SECT;
	if (inr(itop(280, 240), itop(460, 285), itop(bev.x, bev.y)))
		al->edit.stat = EDIT_WALL;
}

void				mouse_press_edit_setting_sector(t_al *al, SDL_MouseButtonEvent bev)
{
	if (inr(itop(45, 400), itop(220, 445), itop(bev.x, bev.y)))
		al->edit.stat = SET_FLO_HEI;
	if (inr(itop(45, 320), itop(220, 365), itop(bev.x, bev.y)))
		al->edit.stat = (al->edit.stat == EDIT_WALL) ? SET_WALL_TEXT : SET_FLO_TEXT;
	if (inr(itop(280, 400), itop(460, 445), itop(bev.x, bev.y)))
		al->edit.stat = SET_CEL_HEI;
	if (inr(itop(280, 320), itop(460, 365), itop(bev.x, bev.y)))
		al->edit.stat = SET_CEL_TEXT;
}

void			mouse_press_edit_menu(t_al *al, SDL_MouseButtonEvent bev)
{
	// if (al->edit.stat == SET_CEL_HEI || al->edit.stat == SET_FLO_HEI)
	// 	printf("x == %d // y == %d \n", bev.x, bev.y);
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
	// else if (al->edit.stat != SET_FLO_TEXT && al->edit.stat != SET_CEL_TEXT)
	else
	{ 
		arrow_stat(al, bev);
		mouse_press_edit_mini_menu(al, bev);
		mouse_press_edit_setting_sector(al, bev);
	}
}

void			mouse_press_edit(t_al *al)
{
	SDL_MouseButtonEvent	bev;

	bev = al->ev.button;
	if (bev.type == SDL_MOUSEBUTTONUP)
		return ;
	// (al->sect) ? print_al(al) : 0;
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
