#include "doom-nukem.h"
#define MAX_SPRITE_DIST 10

void 			display_sprite(t_al *al, t_sprite *cur)
{
	int x;
	int y;
	int i;

	i = -1;
	x = -1;
	while (++x < cur->w)
	{
		y = -1;
		while (++y < cur->h)
		{
			al->pix[x + (y * WIN_SIZEX) ] = cur->tex[++i];
		}
	}
}

void 	display_by_id(t_al *al, int id)
{
	t_sprite *cur;

	cur = al->sprite;
	while (cur->id != id && cur->next != NULL)
		cur = cur->next;
	if (cur != NULL)
		display_sprite(al,cur);
}

int 	found_closer(t_al *al)
{
	t_sprite *cur;
	int id;
	int dist;

	cur = al->sprite;
	id = -1;
	dist = MAX_SPRITE_DIST;
	while (cur != NULL)
	{
		if (cur->dist < dist)
		{
			dist = cur->dist;
			id = cur->id;
		}
		cur = cur->next;
	}
	return (id);
}

int 	found_farther(t_al *al)
{
	t_sprite *cur;
	int id;
	int dist;

	cur = al->sprite;
	id = -1;
	dist = 0;
	while (cur != NULL)
	{
		if (cur->dist > dist)
		{
			dist = cur->dist;
			id = cur->id;
		}
		cur = cur->next;
	}
	return (id);
}
