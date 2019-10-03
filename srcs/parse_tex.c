/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:20:41 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/01 13:57:22 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** We currently arent using this file. just sayin
*/

#include "doom-nukem.h"

void			err_tex(t_al *al)
{
	ft_putstr_fd("Tu veut tbattr ?? QUI T'AS DIT DE TOUCHER LES TEXTURES\n", 2);
	yeet(al);
}

static int 		for_huehue(int fd, unsigned int *pix, unsigned char *buf, int w,
	int h)
{
	int i;
	int j;

	j = h - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < w)
		{
			if (read(fd, buf, 3) != 3)
				return (0);
			pix[j * w + i] = (buf[2] << 16) | (buf[1] << 8)
			| buf[0];
			i++;
		}
		j--;
	}
	// printf("%d\n", h);
	return (1);
}

unsigned int	*parse_tex(t_al *al, char *name, int w, int h)
{
	unsigned char	buf[64];
	int				fd;
	unsigned int	*pix;
	// int				w;
	// int				h;

	pix = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		err_tex(al);
	if (read(fd, buf, 22) != 22 || buf[10] - 22 > 64)
		err_tex(al);
	// w = buf[18] + buf[19] * 256;
	// h = buf[20] + buf[21] * 256;
	// printf("%d\n", /buf[22] + buf[23] * 256);
	// printf("%s => h=%d w=%d\n", name, h, w);
	// for (int u = 0; u < 60; u++){printf("buff[%d] = %d\n", u, buf[u]);}
	
	if (!(pix = ft_memalloc(w * h * sizeof(int))))
		yeet(al);
	read(fd, buf, buf[10] - 22);
	
	if (!for_huehue(fd, pix, buf, w, h))
		yeet(al);
	close(fd);
	return (pix);
}
