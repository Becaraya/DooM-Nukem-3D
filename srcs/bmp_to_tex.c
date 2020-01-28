/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_to_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:39:49 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 11:26:39 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		you_must_install_cs_source_textures(t_tex *tex)
{
	tex->size_x = 2;
	tex->size_y = 2;
	if (!(tex->pix = ft_memalloc(16)))
		return (pr_err(MERROR_MESS));
	tex->pix[0] = 0xffff00ff;
	tex->pix[1] = 0xff000000;
	tex->pix[2] = 0xff000000;
	tex->pix[3] = 0xffff00ff;
	return (0);
}

int		bmp_to_tex(t_tex *tex, char *str, int sizex, int sizey)
{
	char	buf[1000];
	int		fd;
	int		offset;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (you_must_install_cs_source_textures(tex));
	tex->size_x = sizex;
	tex->size_y = sizey;
	if (!(tex->pix = malloc(sizex * sizey * 4)))
		return (pr_err(MERROR_MESS));
	if (read(fd, buf, 14) != 14)
		return (1);
	offset = *(unsigned *)(buf + 10);
	if (read(fd, buf, offset - 14) != offset - 14)
		return (1);
	if (read(fd, tex->pix, sizex * sizey * 4) != sizex * sizey * 4)
		return (1);
	return (0);
}
