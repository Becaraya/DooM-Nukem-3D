/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:45:30 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/25 12:32:12 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** Modular and easy to use .hms encoder *giggles*
*/

int		write_wall(t_walls *wall, int fd)
{
	unsigned char buf[32];

	ft_bzero(buf, 32);
	*(signed int *)(buf + 0) = wall->x1 * 100;
	*(signed int *)(buf + 4) = wall->y1 * 100;
	*(signed int *)(buf + 8) = wall->x2 * 100;
	*(signed int *)(buf + 12) = wall->y2 * 100;
	*(unsigned short *)(buf + 16) = wall->wall_tex;
	*(unsigned short *)(buf + 18) = wall->bot_tex;
	*(unsigned short *)(buf + 20) = wall->top_tex;
	*(unsigned short *)(buf + 22) = wall->is_cross;
	*(unsigned int *)(buf + 24) = wall->sec_lnk;
	if (write(fd, buf, 32) != 32)
		return (1);
	return (0);
}

int		write_walls(t_sector *sec, int fd)
{
	unsigned int	i;

	i = 0;
	while (i < sec->nb_wal)
		write_wall(sec->walls + (i++), fd);
	return (0);
}

int		write_sector(t_sector *sec, int fd)
{
	unsigned char buf[16];

	*(unsigned int *)(buf + 0) = sec->fl_hei * 100.0;
	*(unsigned int *)(buf + 4) = sec->ce_hei * 100.0;
	*(unsigned short *)(buf + 8) = sec->fl_tex;
	*(unsigned short *)(buf + 10) = sec->ce_tex;
	*(unsigned int *)(buf + 12) = sec->nb_wal;
	if (write(fd, buf, 16) != 16)
		return (1);
	if (write_walls(sec, fd))
		return (1);
	return (0);
}

int		write_sectors(t_al *al, int fd)
{
	signed int		buf[4];
	unsigned int	i;

	buf[0] = al->nb_sec;
	buf[1] = al->play.csec;
	buf[2] = al->play.posx * 100;
	buf[3] = al->play.posy * 100;
	if (write(fd, buf, 16) != 16)
		return (1);
	i = 0;
	while (i++ < al->nb_sec)
		if (write_sector(al->sec + i, fd))
			return (1);
	return (0);
}

int		hms_encoder(t_al *al, char *str)
{
	char	buf[1];
	int		l;
	int		fd;

	if ((l = ft_strlen(str)) < 5)
		return (pr_err("Invalid extention, provide a .hms file\n"));
	if (ft_strcmp(str + l - 4, ".hms"))
		return (pr_err("Invalid extention, provide a .hms file\n"));
	if ((fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		return (pr_err("Can't open file\n"));
	if (write_sectors(al, fd))
		return (pr_err("Invalid Data (problem on sectors)\n"));
	//if (write_textures(al, fd))
	//	return (pr_err("Invalid Data (problem on textures)\n"));
	printf("Writing success !\n");
	close(fd);
	return (0);
}
