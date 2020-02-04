/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_to_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:39:49 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 09:19:48 by pitriche         ###   ########.fr       */
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

int		you_must_install_cs_source_textures_pix(unsigned **pix)
{
	if (!(*pix = ft_memalloc(16)))
		return (pr_err(MERROR_MESS));
	(*pix)[0] = 0xffff00ff;
	(*pix)[1] = 0xff000000;
	(*pix)[2] = 0xff000000;
	(*pix)[3] = 0xffff00ff;
	return (0);
}

int		bmp_to_tex(t_tex *tex, char *str, unsigned sizex, unsigned sizey)
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
		exit(pr_err("Invalid texture\n"));
	return (0);
}

int		bmp_to_pix(unsigned **pix, char *str, unsigned sizex, unsigned sizey)
{
	char		buf[1000];
	int			fd;
	int			offset;
	unsigned	i;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (you_must_install_cs_source_textures_pix(pix));
	if (!(*pix = malloc(sizex * sizey * 4)))
		exit(pr_err(MERROR_MESS));
	if (read(fd, buf, 14) != 14)
		exit(1);
	offset = *(unsigned *)(buf + 10);
	if (read(fd, buf, offset - 14) != offset - 14)
		exit(1);
	if (read(fd, *pix, sizex * sizey * 4) != sizex * sizey * 4)
		exit(pr_err("Invalid texture\n"));
	i = 0;
	while (i < sizex * sizey)
	{
		if ((*pix)[i] != 0xffff)
			(*pix)[i] |= 0xff000000;
		i++;
	}
	return (0);
}
