/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:24:58 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/04 16:25:00 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		free_tab(t_al *al)
{
	unsigned	i;

	i = 0;
	if (al->sec)
	{
		while (++i < al->nb_sec)
		{
			free(al->sec[i].walls);
			free(al->rotsec[i].walls);
		}
		free(al->sec);
	}
}

t_point		get_point(double x, double y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	p.color = WHITE;
	return (p);
}

t_walls		*create_walls_elem(t_al *al, unsigned int nb_sec,
	unsigned int nb_wal)
{
	t_walls		*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	data->next = NULL;
	data->wall_tex = al->sec[nb_sec].walls[nb_wal].wall_tex;
	data->top_tex = al->sec[nb_sec].walls[nb_wal].top_tex;
	data->bot_tex = al->sec[nb_sec].walls[nb_wal].bot_tex;
	data->sec_lnk = al->sec[nb_sec].walls[nb_wal].sec_lnk;
	data->is_cross = al->sec[nb_sec].walls[nb_wal].is_cross;
	return (data);
}

t_sector	*create_sector_elem(t_al *al, unsigned int nb_sec)
{
	t_sector	*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_sector))))
		yeet(al);
	data->walls = get_walls(al, nb_sec);
	data->next = NULL;
	data->fl_hei = al->sec[nb_sec].fl_hei;
	data->ce_hei = al->sec[nb_sec].ce_hei;
	data->fl_tex = al->sec[nb_sec].fl_tex;
	data->ce_tex = al->sec[nb_sec].ce_tex;
	data->nb_wal = count_wall(data->walls);
	return (data);
}

t_walls		*get_walls(t_al *al, unsigned int nb_sec)
{
	t_walls			*walls;
	t_walls			*cur;
	unsigned int	nb_wal;

	nb_wal = 0;
	walls = NULL;
	cur = NULL;
	while (nb_wal < al->sec[nb_sec].nb_wal)
	{
		if (walls == NULL)
		{
			walls = create_walls_elem(al, nb_sec, nb_wal);
			cur = walls;
		}
		else
		{
			cur->next = create_walls_elem(al, nb_sec, nb_wal);
			cur = cur->next;
		}
		cur->x1 = al->sec[nb_sec].walls[nb_wal].x1 * 10 + (WIN_SIZEX / 2);
		cur->y1 = -al->sec[nb_sec].walls[nb_wal].y1 * 10 + (WIN_SIZEY / 2);
		cur->x2 = al->sec[nb_sec].walls[nb_wal].x2 * 10 + (WIN_SIZEX / 2);
		cur->y2 = -al->sec[nb_sec].walls[nb_wal++].y2 * 10 + (WIN_SIZEY / 2);
	}
	return (walls);
}
