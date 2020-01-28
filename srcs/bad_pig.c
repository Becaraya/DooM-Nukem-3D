/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_pig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:00:37 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/28 11:30:25 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	badpig(t_al *al, SDL_MouseButtonEvent bev)
{
	t_mob		*tmp;
	unsigned	i;

	if (al->ent == NULL)
	{
		printf("yooo\n");
		if (!(al->ent = ft_memalloc(sizeof(t_mob))))
			yeet(al);
		al->ent->posx = bev.x;
		al->ent->posy = bev.y;
		al->ent->index = 0;
		al->ent->next = NULL;
		return ;
	}
	tmp = al->ent->next;
	if (!(tmp = ft_memalloc(sizeof(t_mob))))
			yeet(al);
	i = 1;
	tmp->next = NULL;
	while (tmp->next)
	{
	printf("biiitte\n",tmp);
		tmp = tmp->next;
		i++;
	}
	tmp->posx = bev.x;
	tmp->posy = bev.y;
	tmp->index = i;
	
	printf("%d",bev.x);
	printf("%d\n",bev.y);
}