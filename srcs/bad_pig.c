/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_pig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:00:37 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/29 14:32:48 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	pig_pos(t_al *al)
{
	t_mob		*mob;
	t_point		point_a;
	t_point		point_b;

	mob = al->ent;
	while (mob != NULL)
	{
		point_a.x = (mob->posx * 10) + (WIN_SIZEX / 2) + 2;
		point_a.y = -(mob->posy * 10) + (WIN_SIZEY / 2) + 2;
		point_b.x = (mob->posx * 10) + (WIN_SIZEX / 2) - 2;
		point_b.y = -(mob->posy * 10) + (WIN_SIZEY / 2) - 2;
		put_rectangle(al->sdlsurf, point_a, point_b, RED);
		mob = mob->next;
	}
}

t_mob	*init_pig(t_al *al, t_mob *mob, t_mob *tmp, unsigned i)
{
	while (tmp->next)
	{
		mob[i].posx = tmp->posx;
		mob[i].posy = tmp->posy;
		mob[i].csec = is_in_sector(al, tmp->posx, tmp->posy);
		mob[i].posz = al->sec[al->ent[0].csec].fl_hei;
		mob[i].velx = 0;
		mob[i].vely = 0;
		mob[i].velz = 0;
		mob[i].gd_vel = 0;
		mob[i].on_ground = 1;
		mob[i].alive = 50;
		mob[i].dir = 0;
		mob[i].size = 2.5;
		mob[i].width = 2.3;
		mob[i].mass = 50;
		mob[i].power = 200;
		mob[i].hit = 1;
		mob[i].index = i;
		mob[i].fly = 1;
		tmp = tmp->next;
		i++;
	}
	return (mob);
}

void	load_pig(t_al *al)
{
	t_mob		*tmp;
	t_mob		*mob;

	al->nb_ent = 0;
	if (al->ent == NULL)
		return ;
	tmp = al->ent;
	while (tmp->next)
	{
		tmp = tmp->next;
		al->nb_ent++;
	}
	if (!(mob = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	if (!(al->rotent = ft_memalloc(al->nb_ent * sizeof(t_mob))))
		yeet(al);
	tmp = al->ent;
	mob = init_pig(al, mob, tmp, 0);
	al->ent = mob;
}

t_mob	*new_mob(t_al *al, SDL_MouseButtonEvent bev, unsigned i)
{
	t_mob		*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_mob))))
		yeet(al);
	data->posx = (bev.x - WIN_SIZEX / 2) / 10;
	data->posy = (bev.y - WIN_SIZEY / 2) / -10;
	data->index = i;
	data->next = NULL;
	return (data);
}

void	badpig(t_al *al, SDL_MouseButtonEvent bev)
{
	t_mob		*cur;
	unsigned	i;

	i = 0;
	if (al->ent == NULL)
	{
		al->ent = new_mob(al, bev, i);
		return ;
	}
	cur = al->ent;
	while (cur->next != NULL)
	{
		cur = cur->next;
		i++;
	}
	cur->next = new_mob(al, bev, i);
}
