/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:56:20 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/29 13:42:13 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		write_texture(t_tex *tex, int fd)
{
	unsigned char buf[16];

	ft_bzero(buf, 16);
	*(unsigned int *)buf = tex->size_x;
	*(unsigned int *)(buf + 4) = tex->size_y;
	if (write(fd, buf, 16) != 16)
		return (1);
	write(fd, tex->pix, tex->size_x * tex->size_y * sizeof(int));
	return (0);
}

int		write_textures(t_al *al, int fd)
{
	unsigned char	buf[16];
	unsigned int	i;

	ft_bzero(buf, 16);
	*(unsigned short *)buf = al->nb_tex;
	if (write(fd, buf, 16) != 16)
		return (1);
	i = 0;
	while (i <= al->nb_tex)
		if (write_texture(al->tex + (i++), fd))
			return (1);
	return (0);
}
