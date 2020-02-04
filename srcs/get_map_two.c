/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:25:11 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/04 16:25:37 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		get_map(t_al *al)
{
	t_sector		*sect;
	t_sector		*cur;
	unsigned int	nb_sec;

	nb_sec = 0;
	cur = NULL;
	sect = NULL;
	while (++nb_sec <= al->nb_sec)
	{
		if (sect == NULL)
		{
			sect = create_sector_elem(al, nb_sec);
			cur = sect;
		}
		else
		{
			cur->next = create_sector_elem(al, nb_sec);
			cur = cur->next;
		}
	}
	al->sect = sect;
}

int			count_wall(t_walls *wall)
{
	int i;

	i = 0;
	while (wall != NULL)
	{
		i++;
		wall = wall->next;
	}
	return (i);
}

int			count_sect(t_sector *sect)
{
	int i;

	i = 0;
	while (sect != NULL)
	{
		i++;
		sect = sect->next;
	}
	return (i);
}

void		get_wall_tab(t_al *al, int nb_sec, t_walls *walls)
{
	unsigned int	nb_wal;

	nb_wal = 0;
	while (walls != NULL)
	{
		al->sec[nb_sec].walls[nb_wal].x1 = (walls->x1 - (WIN_SIZEX / 2)) / 10;
		al->sec[nb_sec].walls[nb_wal].y1 = (walls->y1 - (WIN_SIZEY / 2)) / -10;
		al->sec[nb_sec].walls[nb_wal].x2 = (walls->x2 - (WIN_SIZEX / 2)) / 10;
		al->sec[nb_sec].walls[nb_wal].y2 = (walls->y2 - (WIN_SIZEY / 2)) / -10;
		al->sec[nb_sec].walls[nb_wal].wall_tex = walls->wall_tex;
		al->sec[nb_sec].walls[nb_wal].top_tex = walls->top_tex;
		al->sec[nb_sec].walls[nb_wal].bot_tex = walls->bot_tex;
		al->sec[nb_sec].walls[nb_wal].sec_lnk = walls->sec_lnk;
		al->sec[nb_sec].walls[nb_wal].is_cross = walls->is_cross;
		nb_wal++;
		walls = walls->next;
	}
	al->sec[nb_sec].nb_wal = nb_wal;
}

void		get_sec_tab(t_al *al)
{
	t_sector		*sect;
	unsigned int	nb_sec;

	if (!(al->sec = ft_memalloc(sizeof(t_sector) * count_sect(al->sect) + 2)))
		yeet(al);
	sect = al->sect;
	nb_sec = 1;
	if (!(al->sec[0].walls = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	while (sect != NULL)
	{
		if (!(al->sec[nb_sec].walls = ft_memalloc(sizeof(t_walls) *
			count_wall(sect->walls) + 1)))
			yeet(al);
		get_wall_tab(al, nb_sec, sect->walls);
		al->sec[nb_sec].fl_hei = sect->fl_hei;
		al->sec[nb_sec].ce_hei = sect->ce_hei;
		al->sec[nb_sec].fl_tex = sect->fl_tex;
		al->sec[nb_sec].ce_tex = sect->ce_tex;
		sect = sect->next;
		nb_sec++;
	}
	al->nb_sec = nb_sec - 1;
	free_sect(al->sect);
	al->sect = NULL;
}
