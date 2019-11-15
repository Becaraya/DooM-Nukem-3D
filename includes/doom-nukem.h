/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/15 16:06:24 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <SDL2/SDL.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>

# define WIN_TITLE "100% really slenderman absolutely virus free i swear"
# define WIN_SIZEX 1366
# define WIN_SIZEY 768
# define WIN_POSX 100
# define WIN_POSY 10

# define WIN_EDIT_SIZEX	768
# define WIN_EDIT_SIZEY	768

# define MAX_WALLS_HIT	1000
# define HORIZON_LIMIT	1000

# define D_2PI	8192 // 1<13
# define D_2PIM	8191
# define D_PI	4096
# define D_PI_2	2048
# define D_PI_4	1024

# define DEFAULT_G 9.81
# define DEFAULT_FOV D_2PI * 0.20

#define	SPRITE_W 512
#define	SPRITE_H 512
/*
** TEX_REPEAT is horizontal repeat in m
** TEX_REPEAT_V is vertical repeat in m*(1<<16)
*/

# define TEX_REPEAT 2.0
# define TEX_REPEAT_V 131072

/*
** now this one is very strange. REPEAT_F is repeat distance * 0x10000 - 1
** and it is used as a mask so the -1 is important
** REPEAT_F_DIV is log2 of REPEAT_F + 1, and to emulate a division with a
** bit shift
*/

# define TEX_REPEAT_F		131071
# define TEX_REPEAT_F_DIV	17


# define PLAYER_CROUCH 1.10
# define PLAYER_SIZE 1.78
# define PLAYER_EYE_TOP 0.15
# define PLAYER_MASS 67
# define PLAYER_AERO_POWER 400
# define PLAYER_ANA_POWER 1950

# define LOOK_SENS 1000

# define MERROR_MESS "Malloc error\n"

# define M_2PI 6.283185307179586476925286766559005768394338798750211641949

# define WHITE 0x80ffffff
# define WHITE_L 0xCDCDCD
# define BLACK 0x0
# define LIGHT_GREY 0xb0b0b0
# define DARK_GREY 0x606060

# define BACK_GROUND LIGHT_GREY
# define TEXT_EDITOR BLACK

/*
** just too simplify
*/

# define PPX al->play.posx
# define PPY al->play.posy
# define EPX al->ent.posx
# define EPY al->ent.posy

/*
** ENUMS, for all status ######################################################
*/

/*
** main status
*/

typedef enum		e_status
{
	MENU,
	GAME,
	PAUSE,
	EDIT
}					t_status;

typedef enum		e_status_ed
{
	SELECT,
	FIRST_CLICK,
	DRAWING,
	FIRST_CLICK_REC,
	DRAWING_REC
	
}					t_status_ed;

typedef enum		e_stat_wall
{
	SIMPLE,
	RECT
}					t_stat_wall;

typedef enum		e_ai
{
	NONE
}					t_ai;

/*
** TYPEDEF ####################################################################
*/

typedef	unsigned int	t_angle;

/*
** STRUCTURES #################################################################
*/

/*
** .hms parser and the main game data
*/

typedef struct		s_walls
{
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	unsigned short	wall_tex;
	unsigned short	top_tex;
	unsigned short	bot_tex;
	unsigned short	is_cross;
	unsigned int	sec_lnk;
	struct s_walls	*next;
}					t_walls;

/*
**	fl:floor ce:ceiling hei:height tex:texture index
*/

typedef struct		s_sector
{
	double			fl_hei;
	double			ce_hei;
	unsigned short	fl_tex;
	unsigned short	ce_tex;
	unsigned int	nb_wal;
	t_walls			*walls;
	struct s_sector	*next;
}					t_sector;

typedef struct		s_tex
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	*pix;
}					t_tex;

typedef struct		s_tex_or
{
	unsigned int	**pix;
}					t_tex_or;


typedef struct		s_tex_group
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	nb_tex;
	t_tex_or		or[9];
}					t_tex_group;

/*
** key currently pressed
*/

typedef struct		s_keys
{
	unsigned		w:1;
	unsigned		a:1;
	unsigned		s:1;
	unsigned		d:1;
	unsigned		left:1;
	unsigned		righ:1;
	unsigned		up:1;
	unsigned		down:1;
	unsigned		space:1;
}					t_keys;

typedef struct		s_mouse
{
	unsigned		left:1;
	unsigned		righ:1;
	unsigned		up:1;
	unsigned		down:1;
	unsigned		mouve:1;
	unsigned		click:1;
}					t_mouse;

// typedef struct		s_icon
// {
// 	unsigned int	*chest;
// 	unsigned int	*click;
// 	unsigned int	*path;
// 	unsigned int	*portal;
// 	unsigned int	*wall;
// }					t_icon;

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

// typedef struct		s_wall
// {
// 	int				x1;
// 	int				y1;
// 	int				x2;
// 	int				y2;
// 	t_stat_wall		type;
// 	struct s_wall	*prev;
// 	struct s_wall	*next;
// }					t_wall;

typedef struct		s_edit
{
	t_status_ed		stat;
	int				zoom;
}					t_edit;

/*
** raycast hit limits descripting struct
** first set of limits are non horizon corrected lims, while the 2nd set is
** horizon corrected and screen size capped
*/

typedef struct		s_rc_lim
{
	int	toplim;
	int	topwall;
	int	topmid;
	int	botmid;
	int	botwall;
	int	botlim;

	int	sc_toplim;
	int	sc_topwall;
	int	sc_topmid;
	int	sc_botmid;
	int	sc_botwall;
	int	sc_botlim;
}					t_rc_lim;

/*
** raycast hit descripting struct to add info missing from t_walls
** wall_length is length in m
*/

typedef struct		s_rc_hit
{
	double		hitdst;
	unsigned	hit_texx;
	double		wall_length;
	unsigned	fl_tex;
	double		fl_hei;
	unsigned	ce_tex;
	double		ce_hei;
	t_walls		wall;
	t_rc_lim	lim;
	unsigned	is_entity:1;
}					t_rc_hit;

/*
** raycast ray descripting func to add info missing from t_walls
** xfact and yfact are 16 bits sin and cos of anglem for floorcasting
** min is used in test_hit and is unimportant
*/

typedef struct		s_rc_ray
{
	int			x;
	t_angle		angle;
	int			xfact;
	int			yfact;
	int			nb_hits;
	t_rc_hit	hits[MAX_WALLS_HIT];

	double		min;
}					t_rc_ray;

/*
** Player info struct
** Velocities are in m/s, positions are in m, mass is in kg and power is in watt
** csec: index of current sector, must be updated if crossing sectors
** horizon: height of the horizon in pixels, indicates if lookup or down
** eyez: eye position on z
*/

typedef struct		s_sprite
{
	int 			id;
	int 			w;
	int 			h;
	int 			x;
	int 			y;
	int				angle;
	double			dist;
	unsigned int	*tex;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_player
{
	unsigned	csec;
	double		posx;
	double		posy;
	double		posz;
	double		velx;
	double		vely;
	double		velz;
	double		gd_vel;
	unsigned	on_ground:1;
	unsigned	alive:1;
	t_angle		dir;

	double		size;
	double		eyez;
	double		mass;
	double		power;
	double		power_mult;

	int			horizon;
}					t_player;

/*
** i think some var are usless on entity.
*/

typedef struct		s_mob
{
	unsigned	csec;
	double		posx;
	double		posy;
	double		posz;
	double		velx;
	double		vely;
	double		velz;
	double		gd_vel;
	unsigned	on_ground:1;
	unsigned	alive:1;
	t_angle		dir;

	double		size;
	double		mass;
	double		power;
}					t_mob;

typedef union		u_entity
{
	t_player	pl;
	t_mob		mob;
}					t_entity;

typedef struct		s_text
{
	char			*str;
	SDL_Color		clr;
	SDL_Rect		*where;
}					t_text;

typedef struct		s_text_list
{
	t_text			gen_map;
	t_text			sect_para;
	t_text			x_start;
	t_text			y_start;
	t_text			x_end;
	t_text			y_end;
	t_text			cancel;
}					t_text_list;

/*
** Main structure #############################################################
*/

typedef struct		s_al
{
	t_status		status;
	void			(*stat_fnc[4])(struct s_al *);

	SDL_Window		*sdlwin;
	SDL_Surface		*sdlsurf;
	unsigned		*pix;

	SDL_Window		*win_ed;
	SDL_Surface		*surf_ed;
	unsigned		*pix_ed;

	unsigned		ttf_st:1;
	TTF_Font		*font;
	t_text_list		text;
	SDL_Color		color;

	unsigned int	nb_sec;
	t_sector		*sec;
	t_sector		*rotsec;
	unsigned short	nb_tex;
	unsigned short	nb_texgp;
	t_tex			*tex;
	t_tex_group		*texgp;

	t_entity		*ent;

	t_player		play;
	t_entity		ent;
	double			g;
	t_angle			fov;
	int				stretch;
	int				wall_scale;

	unsigned int	fps;
	long			last_time;
	long			curr_time;
	long			tgt_time;
	int				dtime;

	t_edit			edit;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;

	t_sector		*sect;
	// int				nb_sect;

	double			sin[D_2PI];
	double			cos[D_2PI];
	//double			tan[D_2PI];

	t_sprite 		*sprite;

	char			v0id[32];
}					t_al;

/*
** Prototypes #################################################################
*/

unsigned int		*parse_tex(t_al *al, char *name, int w, int h);
int					pr_err(char *str);

void				init(t_al *al, char *str);
void				main_loop(t_al *al);

void				key_func(t_al *al);
void				mouse_press(t_al *al);
void				mouse_press_edit(t_al *al);
void				mouse_mv(t_al *al);
void				mouse_weel(t_al *al);

double				power_to_run(t_al *al);
void				jump(t_al *al);

t_angle				add_angle(t_angle a1, t_angle a2);
t_angle				sub_angle(t_angle a1, t_angle a2);

void				column(t_al *al, t_rc_ray *ray);

void				refresh(t_al *al);

/*
** free fonction
*/

void				free_wall(t_walls *walls);
void				yeet(t_al *al);
void				get_map(t_al *al);
t_walls				*get_walls(t_al *al, unsigned int nb_sec);
t_walls				*create_walls_elem(t_al *al);
t_sector			*create_sector_elem(t_al *al, unsigned int nb_sec);





/*
** hms parser
*/

int					hms_parser(t_al *al, char *str);
int					check_links(t_sector *sec, unsigned nb_sec);
int					parse_pixels(t_tex *tex, int fd);
int					parse_texture(t_tex *tex, int fd);
int					parse_textures(t_al *al, int fd);
int					parse_sectors(t_al *al, int fd);

int					bmp_to_tex(t_tex *tex, char *str, int sizex, int sizey);

/*
** hms encoder
*/

int					hms_encoder(t_al *al, char *str);
int					write_sectors(t_al *al, int fd);
int					write_textures(t_al *al, int fd);

/*
** status functions
*/

void				editor(t_al *al);
void				menu(t_al *al);
void				game(t_al *al);
void				render(t_al *al);

/*
** sprites functions
*/
void	init_texgrp(t_al *al);
void	display_texgp(t_al *al, unsigned int *pix);

/*
** draw function
*/

void				ft_put_line(t_point a, t_point b, SDL_Surface *surf, int color);
void				put_rectangle(SDL_Surface *surf, t_point a, t_point b, int clr);
/*
** authorization too mooving function
*/

void				ft_nop(t_al *al, int i, double x, double y);
void				ft_nop_player(t_al *al, int i, double x, double y);

/*
** SDL Tools
*/

SDL_Rect			get_rect(int x, int y);
SDL_Color			add_color(int color);

/*
** Tools
*/

t_point				itopoint(int x, int y);


/*
** action of entity
*/
void		acceleration_entities(t_al *al);

#endif
