/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:45:30 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/30 11:32:14 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Modular and easy to use .hms encoder *giggles*
*/

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
	if (write_textures(al, fd))
		return (pr_err("Invalid Data (problem on textures)\n"));
	if (write_texture_groups(al, fd))
		return (pr_err("Invalid Data (problem on texture groups)\n"));
	ft_putstr("Writing success !\n");
	close(fd);
	return (0);
}
