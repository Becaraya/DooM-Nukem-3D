/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:31:46 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/30 14:59:53 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// __attribute__ ((destructor)) void no_end (void);

int		main(int ac, char **av)
{
	t_al	*al;

	if (!(al = ft_memalloc(sizeof(t_al))))
		exit(0);
	if (ac == 1)
		init(al, 0, 1);	
	else if (ac == 2)
		init(al, av[1], 0);
	else if (ac == 3)
	{
		init(al, av[1], 1);
		al->map_write_name = av[2]; 
	}
	main_loop(al);
	return (0);
}

// void	no_end()
// {
// 	while (42);
// }
