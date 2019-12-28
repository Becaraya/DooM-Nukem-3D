/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_parser_texgp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:52:25 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/13 15:32:37 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		parse_texture_group(t_tex_group *tgp, int fd)
{
	unsigned char	buf[12];
	unsigned		or;
	unsigned		tex;

	if (read(fd, buf, 12) != 12)
		return (1);
	tgp->size_x = *(unsigned int *)buf;
	tgp->size_y = *(unsigned int *)(buf + 4);
	tgp->nb_tex = *(unsigned int *)(buf + 8);
	or = 0;
	while (or < 8)
	{
		tgp->or[or].pix = ft_memalloc(tgp->nb_tex * sizeof(unsigned *));
		tex = 0;
		while (tex < tgp->nb_tex)
		{
			tgp->or[or].pix[tex] = malloc(tgp->size_x * tgp->size_y * 4);
			read(fd, tgp->or[or].pix[tex++], tgp->size_x * tgp->size_y * 4);
		}
		or -= -1;
	}
	return (0);
}

int		parse_texture_groups(t_al *al, int fd)
{
	unsigned char	buf[2];
	unsigned int	i;

	if (read(fd, buf, 2) != 2)
		return (1);
	al->nb_texgp = *(unsigned short *)buf;
	al->texgp = ft_memalloc(al->nb_texgp * sizeof(t_tex_group));
	i = 0;
	while (i < al->nb_texgp)
		if (parse_texture_group(al->texgp + (i++), fd))
			return (1);
	return (0);
}
