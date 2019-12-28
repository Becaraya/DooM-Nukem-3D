#include "doom_nukem.h"

void 	free_tab(t_al *al)
{
	int		i;

	i = al->nb_sec;
	if (al->sec)
	{
		while (i != 0)
		{
			free(al->sec[i].walls);
			i--;
		}
		free(al->sec);
	}
}

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

void display_tab(t_al *al)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (++i <= al->nb_sec)
	{
		printf("\nsector %d\n\n",i);
		j = 0;
		while (j < al->sec[i].nb_wal)
		{
			printf("wall %d\n",j);
			printf("x1 = %f\n",al->sec[i].walls[j].x1);
			printf("y1 = %f\n",al->sec[i].walls[j].y1);
			printf("x2= %f\n",al->sec[i].walls[j].x2);
			printf("y2= %f\n",al->sec[i].walls[j].y2);
			j++;
		}

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

t_walls		*create_walls_elem(t_al *al, unsigned int nb_sec, unsigned int nb_wal)
{
	t_walls		*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	data->next = NULL;
	data->wall_tex = al->sec[nb_sec].walls[nb_wal].wall_tex;
	data->top_tex = al->sec[nb_sec].walls[nb_wal].top_tex;
	data->bot_tex = al->sec[nb_sec].walls[nb_wal].bot_tex;
	data->sec_lnk = al->sec[nb_sec].walls[nb_wal].sec_lnk;
	data->is_cross = al->sec[nb_sec].walls[nb_wal].is_cross;
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
	data->fl_hei = al->sec[nb_sec].fl_hei;
	data->ce_hei = al->sec[nb_sec].ce_hei;
	data->fl_tex = al->sec[nb_sec].fl_tex;
	data->ce_tex = al->sec[nb_sec].ce_tex;
	return (data);
}


t_walls		*get_walls(t_al *al, unsigned int nb_sec)
{
	t_walls			*walls;
	t_walls			*cur;
	unsigned int	nb_wal;

	nb_wal = 0;
	walls = NULL;
	cur = NULL;
	while (nb_wal < al->sec[nb_sec].nb_wal)
	{
		if (walls == NULL)
		{
			walls = create_walls_elem(al,nb_sec,nb_wal);
			cur = walls;
		}
		else
		{
			cur->next = create_walls_elem(al,nb_sec,nb_wal);
			cur = cur->next;
		}
		cur->x1 = al->sec[nb_sec].walls[nb_wal].x1 *10 + (WIN_SIZEX / 2);
		cur->y1 = -al->sec[nb_sec].walls[nb_wal].y1 * 10 + (WIN_SIZEY / 2);
		cur->x2= al->sec[nb_sec].walls[nb_wal].x2 * 10 + (WIN_SIZEX / 2);
		cur->y2= -al->sec[nb_sec].walls[nb_wal].y2 * 10 + (WIN_SIZEY / 2);
		nb_wal++;
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
	free_tab(al);
}

int			count_wall(t_walls *wall)
{
	int i;

	i = 0;
	while (wall != NULL)
	{
		i++;
		wall = wall->next;
	}
	return (i);
}

int			count_sect(t_sector *sect)
{
	int i;

	i = 0;
	while (sect != NULL)
	{
		i++;
		sect = sect->next;
	}
	return (i);
}

void		get_wall_tab(t_al *al, int nb_sec, t_walls *walls)
{
	unsigned int	nb_wal;

	nb_wal = 0;
	while (walls != NULL)
	{
		al->sec[nb_sec].walls[nb_wal].x1 = (walls->x1 - (WIN_SIZEX / 2)) / 10;
		al->sec[nb_sec].walls[nb_wal].y1 = (walls->y1 - (WIN_SIZEY / 2)) / -10;
		al->sec[nb_sec].walls[nb_wal].x2 = (walls->x2 - (WIN_SIZEX / 2)) / 10;
		al->sec[nb_sec].walls[nb_wal].y2 = (walls->y2 - (WIN_SIZEY / 2)) / -10;
		al->sec[nb_sec].walls[nb_wal].wall_tex = walls->wall_tex;
		al->sec[nb_sec].walls[nb_wal].top_tex = walls->top_tex;
		al->sec[nb_sec].walls[nb_wal].bot_tex = walls->bot_tex;
		al->sec[nb_sec].walls[nb_wal].sec_lnk = walls->sec_lnk;
		al->sec[nb_sec].walls[nb_wal].is_cross = walls->is_cross;

		nb_wal++;
		walls = walls->next;
	}
	al->sec[nb_sec].nb_wal = nb_wal;
}

void		get_sec_tab(t_al *al)
{
	t_sector		*sect;
	unsigned int	nb_sec;

	if (!(al->sec = ft_memalloc(sizeof(t_sector) * count_sect(al->sect)+1)))
		yeet(al);
	sect = al->sect;
	nb_sec = 1;
	if (!(al->sec[0].walls = ft_memalloc(sizeof(t_walls))))
		yeet(al);
	while (sect != NULL)
	{
		if (!(al->sec[nb_sec].walls = ft_memalloc(sizeof(t_walls) * count_wall(sect->walls)+1)))
			yeet(al);
		get_wall_tab(al,nb_sec,sect->walls);
		al->sec[nb_sec].fl_hei = sect->fl_hei;
		al->sec[nb_sec].ce_hei = sect->ce_hei;
		al->sec[nb_sec].fl_tex = sect->fl_tex;
		al->sec[nb_sec].ce_tex = sect->ce_tex;
		sect = sect->next;
		nb_sec++;
	}
	al->nb_sec = nb_sec - 1;
	free_sect(al->sect);
	al->sect = NULL;
}
