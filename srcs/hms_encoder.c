/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hms_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:45:30 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
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
	printf("Writing success !\n");
	close(fd);
	return (0);
}
