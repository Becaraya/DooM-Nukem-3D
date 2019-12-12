/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:31:46 by becaraya          #+#    #+#             */
/*   Updated: 2019/12/12 16:33:08 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// __attribute__ ((destructor)) void no_end (void);

int		main(int ac, char **av)
{
	t_al	al;

	ft_bzero(&al, sizeof(t_al)); // ça c'est important
	if (ac < 2)
		return (pr_err("No .hms file provided\n"));
	init(&al, av[1]);
	//hms_encoder(&al, "house.hms");
	main_loop(&al);
	return (0);
}

// void	no_end()
// {
//	while (42);
// }
