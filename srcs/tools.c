/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 14:22:25 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/28 11:57:57 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_point			itop(int x, int y)
{
	t_point		res;

	res.x = x;
	res.y = y;
	return (res);
}

int				inr(t_point src_a, t_point src_b, t_point cmp)
{
	if (src_a.x < cmp.x && src_a.y < cmp.y
		&& src_b.x > cmp.x && src_b.y > cmp.y)
		return (1);
	return (0);
}

unsigned int	nb_wall(t_al *al)
{
	t_sector	*tmp_s;
	int			i;

	tmp_s = al->sect;
	i = 0;
	while ((al->nb_sec - i) > al->edit.index_sect)
	{
		tmp_s = tmp_s->next;
		i++;
	}
	return ((tmp_s) ? tmp_s->nb_wal : 0);
}

int				cocmp(SDL_Rect *p1, SDL_Rect *p2)
{
	if (p1->x == p2->x && p1->y == p2->y)
		return (1);
	return (0);
}
