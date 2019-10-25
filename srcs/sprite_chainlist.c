#include "doom-nukem.h"
#define	SPRITE_W 512
#define	SPRITE_H 512


void 				remove_sprite(t_al *al, t_sprite *cur, t_sprite *next, t_sprite *prev)
{
	t_sprite *tmp;

	tmp = NULL;
	if (prev != NULL )
	{

		tmp = prev;
		tmp->next = next;
		ft_memdel((void **)&cur);
	}
	else if (prev == NULL)
	{
		tmp = next;
		al->sprite = tmp;
		ft_memdel((void **)&cur);
	}
}

void 				reset_id(t_al *al)
{
	t_sprite *cur;
	int id;

	cur = al->sprite;
	id = 0;
	while (cur != NULL)
	{
		cur->id = id;
		cur = cur->next;
		id++;
	}
}

void 		remove_sprite_by_id(t_al *al, int id)
{
	t_sprite *cur;
	t_sprite *prev;

  	cur = al->sprite;
	prev = NULL;
	while (cur != NULL)
	{
		if (cur->id == id)
		{
			remove_sprite(al,cur,cur->next,prev);
		}
		prev = cur;
		cur = cur->next;
	}
	if (al->sprite != NULL)
			reset_id(al);
}


void	add_sprite(t_al *al, char *name)
{
	t_sprite *tmp;

	if (al->sprite == NULL)
	{
		al->sprite = create_sprite_elem(al,0,name);
		return ;
	}
	tmp = al->sprite;
	while (tmp->next != NULL)
	 	tmp = tmp->next;
	tmp->next = create_sprite_elem(al,(tmp->id+1),name);
}

t_sprite 	*create_sprite_elem(t_al *al, int id, char *name)
{
	t_sprite *sp;

	if (!(sp = ft_memalloc(sizeof(t_sprite))))
		return (NULL);
	sp->x = 0;
	sp->y = 0;
	sp->id = id;
	sp->angle = 0;
	sp->w = SPRITE_W;
	sp->h = SPRITE_H;
	sp->dist = 10;
	sp->tex = parse_tex(al, name, SPRITE_W,SPRITE_H);
	sp->next = NULL;
	return (sp);
}

void draw_sprite(t_al *al)
{
	// t_sprite *sp;
	al->pix = al->sprite->tex;

}
