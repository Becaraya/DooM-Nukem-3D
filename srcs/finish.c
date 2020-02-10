/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:34:30 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/06 10:36:52 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	finish_write(t_al *al, int true)
{
	if (true)
		exit(0);
	ft_putstr("Map written as [");
	ft_putstr(al->map_write_name);
	ft_putstr("] !\n");
	exit(0);
}

int		pr_err(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	javoue_jabuse1(t_tex_group *tgp, unsigned i, unsigned or)
{
	unsigned	*tmp;

	tmp = tgp->or[or].pix[i];
	if (tmp[0] == 0xffff00ff && tmp[1] == 0xff000000 && tmp[2] ==
	0xff000000 && tmp[3] == 0xffff00ff)
	{
		tgp->size_x = 2;
		tgp->size_y = 2;
		ft_putchar('X');
	}
	else
		ft_putchar('O');
}

/*
** IT'S A PRANK !!!
*/

void	prepare_exit(t_al *al)
{
	(void)al;
	ft_putstr_fd("[1]    9654 segmentation fault  ./doom_nukem\n", 2);
	exit(0);
}
