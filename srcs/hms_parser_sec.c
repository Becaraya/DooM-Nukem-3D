/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_parser_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 11:45:25 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/06 15:03:19 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		parse_wall(t_walls *wall, int fd)
{
	unsigned char buf[32];

	if (read(fd, buf, 32) != 32)
		return (1);
	wall->x1 = *(signed int *)(buf + 0) / 100.0;
	wall->y1 = *(signed int *)(buf + 4) / 100.0;
	wall->x2 = *(signed int *)(buf + 8) / 100.0;
	wall->y2 = *(signed int *)(buf + 12) / 100.0;
	wall->wall_tex = *(unsigned short *)(buf + 16);
	wall->bot_tex = *(unsigned short *)(buf + 18);
	wall->top_tex = *(unsigned short *)(buf + 20);
	wall->sec_lnk = *(unsigned int *)(buf + 24);
	if (wall->sec_lnk)
		wall->is_cross = *(unsigned short *)(buf + 22);
	return (0);
}

int		parse_walls(t_sector *sec, t_sector *rotsec, int fd)
{
	unsigned int	i;

	i = 0;
	if (!(sec->walls = ft_memalloc(sec->nb_wal * sizeof(t_walls))) ||
		!(rotsec->walls = ft_memalloc(sec->nb_wal * sizeof(t_walls))))
		exit(pr_err(MERROR_MESS));
	while (i < sec->nb_wal)
	{
		parse_wall(sec->walls + i, fd);
		if (i != 0)
			if (sec->walls[i].x1 != sec->walls[i - 1].x2 || sec->walls[i].y1
				!= sec->walls[i - 1].y2)
				return (pr_err("Walls not connected\n"));
		i++;
	}
	if (sec->walls[0].x1 != sec->walls[i - 1].x2 || sec->walls[0].y1
		!= sec->walls[i - 1].y2)
		return (pr_err("Walls not connected\n"));
	return (0);
}

int		parse_sector(t_sector *sec, t_sector *rotsec, int fd)
{
	unsigned char buf[16];

	if (read(fd, buf, 16) != 16)
		return (1);
	sec->fl_hei = *(unsigned int *)(buf + 0) / 100.0;
	sec->ce_hei = *(unsigned int *)(buf + 4) / 100.0;
	sec->fl_tex = *(unsigned short *)(buf + 8);
	sec->ce_tex = *(unsigned short *)(buf + 10);
	sec->nb_wal = *(unsigned int *)(buf + 12);
	if (sec->nb_wal < 3)
		return (pr_err("Not enough walls\n"));
	if (parse_walls(sec, rotsec, fd))
		return (1);
	return (0);
}

int		parse_sectors(t_al *al, int fd)
{
	unsigned char	buf[32];
	unsigned int	i;

	if (read(fd, buf, 32) != 32)
		return (1);
	al->nb_sec = *(unsigned int *)(buf + 0);
	al->play.csec = *(unsigned int *)(buf + 4);
	al->play.posx = *(signed int *)(buf + 8) / 100.0;
	al->play.posy = *(signed int *)(buf + 12) / 100.0;
	al->door = *(unsigned int *)(buf + 16);
	al->hard = *(unsigned int *)(buf + 20);
	al->end_sect.x = *(signed int *)(buf + 24);
	al->end_sect.y = *(signed int *)(buf + 28);
	if (!al->play.csec || al->play.csec > al->nb_sec)
		return (pr_err("Invalid starting sector\n"));
	if (!(al->sec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector))) ||
		!(al->rotsec = ft_memalloc((al->nb_sec + 1) * sizeof(t_sector))))
		exit(pr_err(MERROR_MESS));
	i = 0;
	while (i++ < al->nb_sec)
		if (parse_sector(al->sec + i, al->rotsec + i, fd))
			return (1);
	if (check_links(al->sec, al->nb_sec))
		return (1);
	return (0);
}
