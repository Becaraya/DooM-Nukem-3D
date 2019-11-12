#include "doom-nukem.h"

void display(t_al *al)
{
	t_sector *sect;
	t_walls *walls;
	int i;

	i = 0;
	sect = al->sect;
	while (sect != NULL)
	{
		printf("sector %d\n\n",++i);
		walls = sect->walls;

		while (walls != NULL)
		{
			printf("p1 = (%f,%f)\np2 = (%f,%f)\n\n",walls->x1,walls->y1,walls->x2,walls->y2);
			walls = walls->next;
		}
		sect = sect->next;
	}
}

t_point		get_point(double x, double y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	p.color = WHITE;
	return (p);
}

t_walls		*create_walls_elem(t_al *al)
{
	t_walls		*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	data->next = NULL;
	return (data);
}

t_sector	*create_sector_elem(t_al *al, unsigned int nb_sec)
{
	t_sector	*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_sector))))
		yeet(al);
	data->walls = get_walls(al,nb_sec);
	data->next = NULL;
	return (data);
}

t_walls		*get_walls(t_al *al, unsigned int nb_sec)
{
	t_walls			*walls;
	t_walls			*cur;
	unsigned int	nb_wal;

	nb_wal = -1;
	walls = NULL;
	cur = NULL;
	while (++nb_wal <= al->sec[nb_sec].nb_wal)
	{
		if (walls == NULL)
		{
			walls = create_walls_elem(al);
			cur = walls;
		}
		else
		{
			cur->next = create_walls_elem(al);
			cur = cur->next;
		}
		cur->x1 = al->sec[nb_sec].walls[nb_wal].x1 * 10 + (WIN_SIZEX / 2);
		cur->y1 = -al->sec[nb_sec].walls[nb_wal].y1 * 10 + (WIN_SIZEY / 2);
		cur->x2= al->sec[nb_sec].walls[nb_wal].x2 * 10 + (WIN_SIZEX / 2);
		cur->y2= -al->sec[nb_sec].walls[nb_wal].y2 * 10 + (WIN_SIZEY / 2);
	}
	return (walls);
}

void		get_map(t_al *al)
{
	t_sector		*sect;
	t_sector		*cur;
	unsigned int	nb_sec;

	nb_sec = 0;
	cur = NULL;
	sect = NULL;
	while (++nb_sec <= al->nb_sec )
	{
		if (sect == NULL)
		{
			sect = create_sector_elem(al,nb_sec);
			cur = sect;
		}
		else
		{
			cur->next = create_sector_elem(al,nb_sec);
			cur = cur->next;
		}
	}
	al->sect = sect;
}
