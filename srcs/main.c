/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:31:46 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/03 17:44:22 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

__attribute__ ((destructor)) void no_end (void);

void	bzerooo(void *s, size_t n)
{
	while (n & 0b111)
	{
		n--;
		*((char *)s + n) = 0;
	}
	while (n >= 8)
	{
		n -= 8;
		*((long *)s + (n >> 3)) = 0;
	}
}

int		main(int ac, char **av)
{
	t_al	*al;

	if (!(al = malloc(sizeof(t_al))))
		exit(0);
	bzerooo(al, sizeof(t_al));
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

void	no_end()
{
	printf("[end]\n");
	while (42);
}
