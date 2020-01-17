/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:24:15 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/15 20:25:21 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int cross_wall(t_walls a, t_walls b)
{
	t_doint c;
	t_doint d;
	double com;
	double te;

//grod soucie je ne peu pas fair autrement que de forcer le c.x pour obtenire la chose la plus proche possible de si j avais un 0
	if (a.x2 == a.x1)
		c.x = 100000000;
	else
		c.x = (a.y2 - a.y1) / (a.x2 - a.x1);
	if (b.x1 == b.x2)
		c.y = 100000000;
	else
		c.y = (b.y2 - b.y1) / (b.x2 - b.x1);
	d.x = a.y1 - (c.x * a.x1);
	d.y = b.y1 - (c.y * b.x1);

	 if (c.x == c.y)
	 {
		 printf("ils sont paralléle\n");
		 return(0);
	 }
	te = (c.x - c.y) / (d.y - d.x);
	com  = (d.y - d.x) / (c.x - c.y);
	if ((com > a.x1 && a.x2 < com) || (com < a.x1 && a.x2 > com))
	{
		printf ("trops loin !!\n");
		return (0);
	}

		if (a.x1 == com && a.y1 == te)
		{
			printf("dans le mille\n");
			//return(0);
		}
		if (a.x2 == com && a.y2 == te)
		{
			printf("dans le mille\n");
			//return(0);
		}
		if (b.x1 == com && b.y1 == te)
		{
			printf("dans le mille\n");
			//return(0);
		}
		if (b.x2 == com && b.y2 == te)
		{
			printf("dans le mille\n");
			//return(0);
		}
		printf("sa traversse !!\n");	
		printf("c.x = %f c.y = %f d.x = %f d.y = %f com = %f te = %f\n", c.x, c.y, d.x, d.y, com,te);
return(1);
} 