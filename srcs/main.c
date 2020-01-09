/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:31:46 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/09 12:16:07 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// __attribute__ ((destructor)) void no_end (void);

int		main(int ac, char **av)
{
	t_al	al;

//son();
	ft_bzero(&al, sizeof(t_al));
	if (ac < 2)
		return (pr_err("No .hms file provided\n"));
	init(&al, av[1]);
	//hms_encoder(&al, "housetexgp.hms");
	main_loop(&al);
	return (0);
}

// void	no_end()
// {
// 	while (42);
// }
