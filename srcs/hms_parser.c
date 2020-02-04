/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:39:49 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 16:53:41 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Modular and easy to use .hms parser *giggles*
*/

void	init_sec_tex(t_al *al)
{
	if (al->sec)
	{
		while (al->nb_sec--)
			free(al->sec[al->nb_sec + 1].walls);
		free(al->sec);
	}
	al->nb_sec = 0;
	al->sec = 0;
	if (al->tex)
	{
		while (al->nb_tex--)
			free(al->tex[al->nb_tex + 1].pix);
		free(al->tex);
	}
	al->nb_tex = 0;
	al->tex = 0;
}

int		check_link(t_sector *sec, t_walls *wall)
{
	unsigned i;

	i = 0;
	while (i < sec->nb_wal)
	{
		if ((sec->walls[i].x1 == wall->x1 && sec->walls[i].y1 == wall->y1
			&& sec->walls[i].x2 == wall->x2 && sec->walls[i].y2 == wall->y2)
			|| (sec->walls[i].x1 == wall->x2 && sec->walls[i].y1 == wall->y2
			&& sec->walls[i].x2 == wall->x1 && sec->walls[i].y2 == wall->y1))
			return (sec->walls[i].sec_lnk ? 0 : 1);
		i++;
	}
	return (1);
}

int		check_links(t_sector *sec, unsigned nb_sec)
{
	unsigned	i;
	unsigned	j;

	i = 0;
	while (++i <= nb_sec)
	{
		j = 0;
		while (j < sec[i].nb_wal)
		{
			if (sec[i].walls[j].sec_lnk)
				if (check_link(sec + sec[i].walls[j].sec_lnk, sec[i].walls + j)
					|| sec[i].walls[j].sec_lnk == i)
					return (pr_err("Invalid link\n"));
			j++;
		}
	}
	return (0);
}

int		parse_ent(t_al *al, int fd)
{
	signed int		buf[2];
	unsigned int	i;

	if (read(fd, buf, 4) != 4)
		return (1);
	al->nb_ent = buf[0];
	if (!al->nb_ent)
		return (0);
	if (!(al->ent = ft_memalloc(al->nb_ent * sizeof(t_entity))))
		exit(0);
	if (!(al->rotent = ft_memalloc(al->nb_ent * sizeof(t_entity))))
		exit(0);
	i = 0;
	while (i < al->nb_ent)
	{
		if (read(fd, buf, 8) != 8)
			return (1);
		al->ent[i].posx = buf[0] / 100.0;
		al->ent[i].posy = buf[1] / 100.0;
		init_pig(al, al->ent, al->ent + i, i);
		i++;
	}
	return (0);
}

int		hms_parser(t_al *al, char *str)
{
	char	buf[1];
	int		l;
	int		fd;

	if ((l = ft_strlen(str)) < 5)
		return (pr_err("Invalid extention, provide a .hms file\n"));
	if (ft_strcmp(str + l - 4, ".hms"))
		return (pr_err("Invalid extention, provide a .hms file\n"));
	if ((fd = open(str, O_RDONLY)) < 0)
		return (pr_err("Can't open file\n"));
	init_sec_tex(al);
	if (parse_sectors(al, fd))
		return (pr_err("Invalid File (problem on sectors)\n"));
	if (parse_ent(al, fd))
		return (pr_err("Invalid Data (problem on entities)\n"));
	if (parse_textures(al, fd))
		return (pr_err("Invalid File (problem on textures)\n"));
	if (parse_texture_groups(al, fd))
		return (pr_err("Invalid File (problem on texture groups)\n"));
	if (read(fd, buf, 1))
		return (pr_err("Invalid File (too long)\n"));
	ft_putstr("Parsing success !\n");
	close(fd);
	return (0);
}
