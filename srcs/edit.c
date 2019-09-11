/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:08:37 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/11 13:20:26 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"


// static void		icon_edit(t_al *al)
// {
// 	for (int i = 0; i < 699; i++){
// 		for (int j = 0; j < 604; j++){
// 			al->pix[699 * j + i] = al->txt.ic.chest[j * 699 + i];
// 		}
// 	}
// }

static void		set_edit(t_al *al)
{
	/* si tu veut init une grosse zone a null utilise bzero plutot  que des for
	ou while. Et fait des typedef sur la win_size plutot que hardcode les val */
	ft_bzero(al->pix, 1280 * 720 * sizeof(int));
}

int		ft_abs(int value)
{
	if (value < 0)
		value = -value;
	return (value);
}

void			ft_put_line(t_point a, t_point b, t_al *al)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			tab[2];

	delta.x = ft_abs(b.x - a.x);
	delta.y = ft_abs(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	tab[0] = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		al->pix[cur.x + cur.y * WIN_SIZEX] = 0xffffff;
		// printf("x = %d y = %d\n", cur.x, cur.y);
		if ((tab[1] = tab[0] * 2) > -delta.y)
		{
			tab[0] -= delta.y;
			cur.x += sign.x;
		}
		if (tab[1] < delta.x)
		{
			tab[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void		draw_wall(t_al *al, t_wall *wall)
{
	t_point		a;
	t_point		b;

	a.x = wall->x1;
	a.y = wall->y1;
	b.x = wall->x2;
	b.y = wall->y2;
	ft_put_line(a, b, al);
	if (wall->next)
		draw_wall(al, wall->next);
}

void	editor(t_al *al)
{
	set_edit(al);
	if (al->c_wall > 0)
		draw_wall(al, al->wall);
	if (al->k.space == 1 && al->edit.stat == T_WALL_IDLE) 
	{
		al->edit.stat = T_WALL_DRAWING;
		al->wall->x1 = 0;
		al->wall->y1 = 0;
		al->wall->x2 = 0;
		al->wall->y2 = 0;
	}
	// icon_edit(al);
	refresh(al);
}
