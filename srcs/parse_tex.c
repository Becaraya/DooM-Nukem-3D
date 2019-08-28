/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:20:41 by pitriche          #+#    #+#             */
/*   Updated: 2019/08/28 16:41:16 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			err_tex(t_al *al)
{
	ft_putstr_fd("Tu veut tbattr ?? QUI T'AS DIT DE TOUCHER LES TEXTURES\n", 2);
	yeet(al);
}

unsigned int	*parse_tex(t_al *al, char *name)
{
	// unsigned char	buff[64];
	// int				fd;
	unsigned int		*pix;

	pix = 0;
	// if ((fd = open(name, O_RDONLY)) < 0)
	// 	err_tex(al);
	// if (read(fd, buf, 14) != 14 || buf[10] - 14 > 64)
	// 	err_tex(al);
	// int width = *(int*)&buff[18];
    // int height = *(int*)&buff[22];

	// printf("w ==%d//h ==%d\n", width, height);
	// close(fd);

	return (pix);
}
