#include "doom_nukem.h"

void	set_spawn(t_al *al, SDL_MouseButtonEvent spw)
{
	al->play.posx = (spw.x - (WIN_SIZEX / 2)) / 10;
	al->play.posy = (spw.y - (WIN_SIZEY / 2)) / -10;
}

void	set_end(t_al *al, SDL_MouseButtonEvent bev)
{
	al->end_sect.x = (bev.x - (WIN_SIZEX / 2)) / 10;
	al->end_sect.y = (bev.y - (WIN_SIZEY / 2)) / -10;
}
