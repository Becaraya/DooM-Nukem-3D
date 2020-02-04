/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:45:30 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 16:22:13 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Modular and easy to use .hms encoder *giggles*
*/

int		write_ent(t_al *al, int fd)
{
	signed int		buf[2];
	unsigned int	i;

	buf[0] = al->nb_ent;
	if (write(fd, buf, 4) != 4)
		return (1);
	i = 0;
	while (i < al->nb_ent)
	{
		buf[0] = al->ent[i].posx * 100;
		buf[1] = al->ent[i].posy * 100;
		if (write(fd, buf, 8) != 8)
			return (1);
		i++;
	}
	return (0);
}

int		hms_encoder(t_al *al, char *str)
{
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
	if (write_ent(al, fd))
		return (pr_err("Invalid Data (problem on sectors)\n"));
	if (write_textures(al, fd))
		return (pr_err("Invalid Data (problem on textures)\n"));
	if (write_texture_groups(al, fd))
		return (pr_err("Invalid Data (problem on texture groups)\n"));
	ft_putstr("\nWriting success !\n");
	close(fd);
	return (0);
}
