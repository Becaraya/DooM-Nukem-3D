/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_parser_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:39:49 by pitriche          #+#    #+#             */
/*   Updated: 2019/11/28 14:48:12 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		parse_pixels(t_tex *tex, int fd)
{
	if (!(tex->pix = ft_memalloc(tex->size_x * tex->size_y * sizeof(int))))
		exit(pr_err(MERROR_MESS));
	read(fd, tex->pix, tex->size_x * tex->size_y * sizeof(int));
	//printf("parsing tex:\n[%6x %6x\n%6x %6x\n", tex->pix[0], tex->pix[1], tex->pix[2], tex->pix[3]);
	return (0);
}

int		parse_texture(t_tex *tex, int fd)
{
	unsigned char buf[16];

	if (read(fd, buf, 16) != 16)
		return (1);
	tex->size_x = *(unsigned int *)buf;
	tex->size_y = *(unsigned int *)(buf + 4);
	if (!tex->size_x || !tex->size_y)
		return (pr_err("Null sized texture\n"));
	if (parse_pixels(tex, fd))
		return (1);
	return (0);
}

int		parse_textures(t_al *al, int fd)
{
	unsigned char	buf[16];
	unsigned int	i;

	if (read(fd, buf, 16) != 16)
		return (1);
	al->nb_tex = *(unsigned short *)buf;
	if (!(al->tex = ft_memalloc((al->nb_tex + 1) * sizeof(t_tex))))
		exit(pr_err(MERROR_MESS));
	i = 0;
	while (i <= al->nb_tex)
	{
		if (parse_texture(al->tex + i, fd))
			return (1);
		// printf("Parsed text %u[%d,%d]]\n\n", i, al->tex[i].size_x, al->tex[i].size_y);
		i++;
	}
	return (0);
}
