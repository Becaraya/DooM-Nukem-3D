/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_parser_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:39:49 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/25 10:45:17 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		bmp_to_tex(t_tex *tex, char *str, int sizex, int sizey)
{
	char	buf[1000];
	int		fd;
	int		offset;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (pr_err("Can't open image\n"));
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
