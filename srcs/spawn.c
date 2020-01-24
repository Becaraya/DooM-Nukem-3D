#include "doom_nukem.h"

void	set_spawn(t_al *al, SDL_MouseButtonEvent spw)
{
	al->play.posx = (spw.x - (WIN_SIZEX / 2)) / 10;
	al->play.posy = (spw.y - (WIN_SIZEY / 2)) / -10;
}
