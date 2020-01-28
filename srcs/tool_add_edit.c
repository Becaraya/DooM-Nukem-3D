/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_add_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:10:14 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 11:57:21 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				check_end_sector(t_walls *wall, int x, int y)
{
	t_walls		*tmp;

	tmp = wall;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->x1 == x && tmp->y1 == y)
		return (1);
	return (0);
}

void			check_can_add(t_al *al, t_sector *sect, t_point coo)
{
	t_point		tmp;
	t_sector	*stmp = NULL;

	tmp.x = coo.x - (coo.x % al->edit.zoom);
	tmp.y = coo.y - (coo.y % al->edit.zoom);
	stmp = al->sect;
	if (sect->walls->next && sect->walls->next->x1 == tmp.x
		&& sect->walls->next->y1 == tmp.y)
		return ;
	add_wall(al, al->sect, coo);
}

void			delonesect(t_sector **sect)
{
	t_sector	*tmp;

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
