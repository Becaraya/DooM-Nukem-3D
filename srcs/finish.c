/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:34:30 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/04 16:20:51 by hutricot         ###   ########.fr       */
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
