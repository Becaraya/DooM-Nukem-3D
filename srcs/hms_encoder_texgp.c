/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder_texgp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:22:27 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/30 14:57:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		write_texture_group(t_tex_group *tgp, int fd)
{
	unsigned char	buf[12];
	unsigned		or;
	unsigned		tex;

	ft_bzero(buf, 12);
	*(unsigned int *)buf = tgp->size_x;
	*(unsigned int *)(buf + 4) = tgp->size_y;
	*(unsigned int *)(buf + 8) = tgp->nb_tex;
	if (write(fd, buf, 12) != 12)
		return (1);
	or = 0;
	while (or < 8)
	{
		tex = 0;
		while (tex < tgp->nb_tex)
			write(fd, tgp->or[or].pix[tex++], tgp->size_x * tgp->size_y * 4);
		or -= -1;
	}
	return (0);
}

int		write_texture_groups(t_al *al, int fd)
{
	unsigned char	buf[2];
	unsigned int	i;

	*(unsigned short *)buf = al->nb_texgp;
	if (write(fd, buf, 2) != 2)
		return (1);
	i = 0;
	while (i < al->nb_texgp)
		if (write_texture_group(al->texgp + (i++), fd))
			return (1);
	return (0);
}
