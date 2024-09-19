/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:08:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 14:45:32 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
// # include <string.h>
# include "mlx_linux/minilibx-linux/mlx.h"
# include "mlx_linux/minilibx-linux/mlx_int.h"
# include "printf/ft_printf.h"
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>
# include <sys/wait.h>

# define FAIL EXIT_FAILURE
# define SUCCESS EXIT_SUCCESS
# define STDERR STDERR_FILENO

# define M_PI 3.14159265358979323846	/* pi */

// Debug

# ifndef DEBUG
// #  define TRACE(...)
// #  define INFO(...)
// #  define WARN(...)
// #  define ERR(...)
#  define DEBUG 0
# else
// #  define TRACE(...) printf("[\x1B[36mTRACE\x1B[0m] " __VA_ARGS__)
// #  define INFO(...) printf("[\x1B[33mINFO\x1B[0m] " __VA_ARGS__)
// #  define WARN(...) printf("[\x1B[35mWARN\x1B[0m] " __VA_ARGS__)
// #  define ERR(...) printf("[\x1B[31mERR\x1B[0m] " __VA_ARGS__)
#  define DEBUG 1
# endif

// Sounds

# ifndef MANDATORY
#  define ACTIVATE_SOUND 1
#  define MANDATORY 0
# else
#  define ACTIVATE_SOUND 0
#  define MANDATORY 1
# endif

# ifndef MINIAUDIO_IMPLEMENTATION
#  define MINIAUDIO_IMPLEMENTATION
#  define MA_NO_PULSEAUDIO
#  define MA_NO_ENCODING
#  define MA_NO_GENERATION
#  define MA_NO_RUNTIME_LINKING
#  define MA_NO_JACK
#  include "miniaudio/miniaudio.h"
# endif

// Colors

# define BOLD "\033[1m"
# define LIL_RED "\033[0;31m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"

# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RCOLOR "\033[1;0m"

# define G_P 0x0000FF00
# define BU_P 0x000000FF
# define R_P 0x00FF0000
# define B_P 0x000000
# define W_P 0xFFFFFF

// Errors Messages

// Parsing
# define E_ARG "Usage: ./cub3D *.cub"

# define ERRCF "Closing file failed\n"
# define ERROF "Opening file failed\n"
# define ERRBA "BAD arguments\n\n"
# define ERRRES "BAD Resolutions arguments\n\n"
# define ERRGNL "GNL Error\n\n"
# define ERRMALL "Malloc failed\n"
# define ERRNUMC "Number of characters per row/col not consistent\n"
# define ERRINVC "Invalid character in the map \n"
# define ERRMNC "Map not closed\n"
# define ERRDUP "Duplicate player/exit in the map\n"
# define ERROR "Error"
# define ERRFF "Exit unreachable / All Collectibles can\'t be collected\n"

// Resolutions

# define XSET_0 "xset r rate 500 33"
# define XSET_1 "xset r rate 100 12"
# define XSET_2 "xset r rate 100 33"
# define XSET_3 "xset r rate 500 12"
# define K_2 "xset r rate 100 15"
# define W_H 600
# define W_W 800
// # define W_H		1080
// # define W_W		1920

# define TOOLBAR_LINUX_H 70

#define LOOKUP_MAX 500

# define SPACE 48
# define WALL 49
# define COLLECT 67
# define EXIT 69
# define SPAWN 80
# define GUARD 71
# define N 78
# define S 83
# define E 69
# define W 87

// # define FONT1 "-sony-fixed-medium-r-normal--17-120-100-100-c-0-iso8859-1"
// # define FONT2 "-sony-fixed-medium-r-normal--24-230-75-75-c-0-iso8859-1"
# define FONT1 "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1"
# define FONT2 "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1"
// # define FONT2 "-sun-open look glyph-----19-190-75-75-p-154-sunolglyph-1"

// Mr. Potato-Head by Joan Stark
# define POTATO "\
\t\t\t\t\t\t\t              .-\"'\"-.\n\
\t\t\t\t\t\t\t             |       |  \n\
\t\t\t\t\t\t\t           (`-._____.-')\n\
\t\t\t\t\t\t\t        ..  `-._____.-'  ..\n\
\t\t\t\t\t\t\t      .', :./\'.== ==.`\\.: ,`.\n\
\t\t\t\t\t\t\t     : (  :   ___ ___   :  ) ;\n\
\t\t\t\t\t\t\t     '._.:    |0| |0|    :._.'\n\
\t\t\t\t\t\t\t        /     `-'_`-'     \\ \n\
\t\t\t\t\t\t\t      _.|       / \\       |._ \n\
\t\t\t\t\t\t\t    .-.-|      (   )      |-.-. \n\
\t\t\t\t\t\t\t   /'   |  .-\"`\"`-'\"`\"-.  |   \\\\ \n\
\t\t\t\t\t\t\t  ||    |  `~\":-...-:\"~`  |    || \n\
\t\t\t\t\t\t\t  ||     \\.    `---'    ./     || \n\
\t\t\t\t\t\t\t  ||       '-._     _.-'       || \n\
\t\t\t\t\t\t\t /  \\       _/ `~:~` \\_       /  \\ \n\
\t\t\t\t\t\t\t||||\\)   .-'    / \\    `-.   (/|||| \n\
\t\t\t\t\t\t\t\\|||    (`.___.')-(`.___.')    |||/ \n\
\t\t\t\t\t\t\t '\"'     `-----'   `-----'     '\"' \n"

# define CUB3D "\
 _____  _   _ ______  _____ ______ \n\
/  __ \\| | | || ___ \\|____ ||  _  \\ \n\
| /  \\/| | | || |_/ /    / /| | | |\n\
| |    | | | || ___ \\    \\ \\| | | |\n\
| \\__/\\| |_| || |_/ /.___/ /| |/ / \n\
 \\____/ \\___/ \\____/ \\____/ |___/  \n"

# define BONUS "\
\t\t\t\t          )      )         (     \n\
\t\t\t\t   (   ( /(   ( /(         )\\ )  \n\
\t\t\t\t ( )\\  )\\())  )\\())    (  (()/(  \n\
\t\t\t\t )((_)((_)\\  ((_)\\     )\\  /(_)) \n\
\t\t\t\t((_)_   ((_)  _((_) _ ((_)(_))   \n\
\t\t\t\t | _ ) / _ \\ | \\| || | | |/ __|  \n\
\t\t\t\t | _ \\| (_) || .' || |_| |\\__ \\  \n\
\t\t\t\t |___/ \\___/ |_|\\_| \\___/ |___/  \n\
\t\t\t\t                                 \n"

// # define M_PI 3.14

# define SOUND_GENERIC "resources/sounds/kek.mp3"
# define SOUND_FOOTSTEPWALK "resources/sounds/Horror\
/Character/Footsteps_walking.wav"
# define SOUND_AMBIENT "resources/sounds/Horror\
/Ambient/Crying_moaning_ambience_2.wav"
# define SOUND_BABYLAUGH1 "resources/sounds/Horror\
/Monsters & Ghosts/Child laugh_6.wav"
# define SOUND_BABYLAUGH2 "resources/sounds/Horror\
/Monsters & Ghosts/Child laugh.wav"
# define SOUND_BABYLAUGH3 "resources/sounds/Horror\
/Monsters & Ghosts/Child laugh_7.wav"
# define SOUND_BUTTONCLICK1 "resources/sounds/Horror\
/House & Office/Can_clink_4.wav"
# define SOUND_BUTTONCLICK2 "resources/sounds/Horror\
/House & Office/switch3.wav"
# define SOUND_GUARDINJURED "resources/sounds/Horror\
/Monsters & Ghosts/Zombie.wav"
# define SOUND_GUARDDEATH "resources/sounds/Horror\
/Monsters & Ghosts/Zombie_8.wav"
# define SOUND_ATTACK "resources/sounds/Horror\
/Monsters & Ghosts/Injured.wav"
# define SOUND_CREDITS "resources/sounds/musics/wav/Ambient 2.wav"
# define SOUND_GAMEOVER "resources/sounds/musics/wav/Fx 3.wav"
# define SOUND_WIN "resources/sounds/musics/wav/Fx 1.wav"

typedef enum s_soundl
{
	EGENERIC,
	EFOOTWALK,
	EAMBIENT,
	EBABY1,
	EBABY2,
	EBABY3,
	EBUTTC1,
	EBUTTC2,
	EGUARDI,
	EGUARDD,
	EATT,
	ECRED,
	ELOSE,
	EWIN,
	SOUND_NB
}						t_soundl;

typedef enum s_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	DIR_N
}						t_dir;

// ERUN,
// EDAMAGED,
// EPICKUP,
// EDIE,
typedef enum s_anim
{
	EWALK,
	EATTACK,
	ANIM_N
}						t_anim;

typedef enum s_door_state
{
	EOPEN,
	ECLOSE,
	EOPENING,
	ECLOSING
}						t_door_state;

typedef enum s_components
{
	EMAP,
	ESPACE,
	EWALL,
	EDOOR,
	EWEAPON,
	EGUARD,
	ESKYBOX,
	ETITLE,
	EMENUSELECT,
	EMENU,
	EMENUIG,
	EMENUOPT,
	COMP_N
}						t_comp;

typedef struct s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct s_point2
{
	double				x;
	double				y;
	int					z;
	int					t;
}						t_point2;


typedef struct s_map
{
	int					x;
	int					y;
	int					z;
	char				val;
	int					rev;
	struct s_map		*right;
	struct s_map		*left;
	struct s_map		*up;
	struct s_map		*down;
}						t_map;

typedef struct s_imga
{
	void				*img;
	struct s_imga		*anim;
	int					animnb;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
	int					width;
	int					height;
	char				*filename;
	char				*fontname;
	char				*fontname2;
	double				posx;
	double				posy;
	int					xdelta;
	int					ydelta;
	int					animx;
	int					animy;
	int					id;
}						t_imga;

typedef struct s_ray
{
	double				camera_x;
	double				dir_x;
	double				dir_y;
	double				dir_x1;
	double				dir_y1;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	double				sidedist_x;
	double				sidedist_y;
	double				deltadist_x;
	double				deltadist_y;
	double				wall_dist;
	double				wall_x;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					pitch;
	int					tx0;
	int					tx1;
	int					dtx;
	int					dy;
	int					dty;
	int					ty0;
	t_map				*hit;
	t_imga				img;
	int					*zbuffer;
}						t_ray;

typedef struct s_sprite
{
	int					drawstartx;
	int					drawstarty;
	int					drawendx;
	int					drawendy;
	int					spritescreenx;
	int					vmovescreen;
	int					spritewidth;
	int					spriteheight;
	double				transformy;
}						t_sprite;



typedef struct s_door
{
	t_point				*d;
	int					nb;
}						t_door;

typedef struct s_trig
{
	double				cosx;
	double				sinx;
	double				cosy;
	double				siny;
	double				cosz;
	double				sinz;
}						t_trig;

typedef struct s_mouse
{
	int					button;
	int					prevx;
	int					prevy;
	int					renderrate;
	long double			zoom;
	long double			xoff;
	long double			yoff;
	double				xangle;
	double				yangle;
	double				zangle;
	float				zheight;
}						t_mouse;

typedef struct s_sound
{
	ma_result			result;
	ma_engine			engine;
	ma_sound			sound[SOUND_NB];
	ma_context			context;
	ma_device_config	deviceconfig;
	float				volume;
	int					init;
}						t_sound;

typedef struct s_player
{
	t_map				*player;
	int					pattack;
	int					animp;
	int					nbmove;
	int					moving;
	int					dir;
	double				x;
	double				y;
	double				z;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				angle;
	double				movespeedx;
	double				movespeedy;
	double				rotspeed;
	double				mouserotspeed;
	uint64_t			timerplayer;
	int					pocket;
}						t_player;

typedef struct s_guard
{
	t_map				*guard;
	int					movingguard;
	int					guarddir;
	int					guarddeath;
	int					guardhp;
	int					guardhit;
	uint64_t			timerguarddir;
	uint64_t			timerguard;
}						t_guard;

typedef struct s_mapv
{
	t_map				*map;
	int					mapvalid;
	int					error;
	int					mapw;
	int					maph;
	int					tmpx;
	int					tmpy;
	int					resdeltax;
	int					resdeltay;
	int					shiftx;
	int					shifty;
	char				*filename;
}						t_mapv;

typedef struct s_objs
{
	t_point				*objs;
	int					initobjs;
	uint64_t			timerobjs;
	int					collect;
}						t_objs;

typedef struct s_proj
{
	int					atttravel;
	int					atttravelframe;
	int					dirproj;
}						t_proj;

typedef struct s_menu
{
	int					menui;
	int					menu;
}						t_menu;

typedef struct s_screen
{
	void				*win;
	long				resw;
	long				resh;
	int					screenw;
	int					screenh;
}						t_screen;

typedef struct s_game
{
	int					pause;
	int					start;
	int					fps;
	uint64_t			created_at;
	uint64_t			updated_at;
	int					won;
	int					refreshmap;
	int					god;
}						t_game;

// images: verifier que le path finit bien par .xpm, que le fichier existe,
// 		qu'on a les permissions pour louvrir.
// couleur: entre 0 et 255

// Map: - Ne peut pas avoir de
typedef struct s_infos
{
	char				*north_path;
	char				*south_path;
	char				*east_path;
	char				*west_path;

	int					ceil;
	int					floor;

}						t_infos;

typedef struct s_vars
{
	t_infos				infos;
	t_xvar				*mlx;
	t_imga				*img;
	t_mouse				mouse;
	t_map				*exit;
	t_map				*last;
	t_trig				trig;
	t_sound				sound;
	t_game				game;
	t_screen			screen;
	t_menu				menu;
	t_proj				proj;
	t_door				door;
	t_objs				objs;
	t_mapv				mapv;
	t_guard				guard;
	t_player			player;
	t_ray				ray;
	t_sprite			sprite;
	uint32_t			tex[8][4160];
}						t_vars;

// Parsing
void				parsing(char *file, t_infos *v);
// Utils
void				showparams(t_vars *v);
int					parse(t_vars *vars, int j, t_map *p);
int					flood_fill(t_vars *v, t_map **tmp, int *i);
t_map				*new_point(t_vars *v, char val, t_map **p);
void				add_element(t_map **vars, t_map **node, t_map **tmp,
						t_map **left);
int					printmap(t_vars *vars, int i);
int					printmap2(t_vars *v);
void				prterr(t_vars *v, char *err, int cleardatab, int init);
void				perr(const char *s);
void				merr(const char *s);
int					myrand(int nb);
t_point2			get_90_angle(int dir, double x, double y);
float				deg_to_rad(float deg);
float				rad_to_deg(float rad);

// Time

uint64_t			timestamp_in_ms(t_vars *v);
void				scrolling(t_vars *v, float *h, char *str, t_point2 p);
// int			timer(int delay);

// Clear
int					clearimgs(t_vars *v);
int					freeall(char **tab);
int					cleardata(t_vars *vars, int b);
int					map_clear(t_map *lst);

// Init
void				init(t_vars *v, int argc, char **argv);
void				inittextures(t_vars *v, int i);
void				initplayeranim(t_vars *v, int d);
void				initobjectsanim(t_vars *v, int i, int obj);
void				initguardanim(t_vars *v, int i);
void				init_cam(t_vars *vars);
void				initmodes(t_vars *v, int argc);
void				initsounds(t_vars *v);
void				initimage(t_vars *v, int index);
void				initvars(t_vars *v);
void				initwindow(t_vars *v, int argc, char **argv);
void				initpathtext(t_vars *v);
void				initplayerpathanim(t_vars *v);
void				initprojectilepathanim(t_vars *v);
void				init_player_dir(t_vars *v);

// Mouse

int					mouse_up(int button, int x, int y, t_vars *p);
int					mouse_down(int button, int x, int y, t_vars *p);
void				zoom(int button, t_vars *vars);
int					mouse_move(int x, int y, t_vars *p);

// Closing / Hooks

int					keys(int keycode, t_vars *vars);
int					closecross(t_vars *vars);
void				hooks(t_vars *vars);
void				resetpos(t_vars *v, int renderb);
void				hotreload(t_vars *vars);
int					keys_release(int keycode, t_vars *v);
void				menuexit(t_vars *v);
void				menuarrow(t_vars *v, int d);
void				menuoptions(t_vars *v);

// Rendering

int					raycasting(t_vars *v);
void				set_dda(t_vars *v);
void				perform_dda(t_vars *v, int d);
void				loadtexture(t_vars *v);
// int					hashit(t_vars *v, int x, int y);
void				set_floor_ceiling_horiz(t_vars *v);
void				set_floor_ceiling_vert(t_vars *v, t_point p);
void				draw_sprites(t_vars *v, t_sprite *sp, t_point p);
void				draw_skybox(t_vars *v, t_point p, int tx, int ty);

int					render(t_vars *data);
void				img_pix_put(t_imga *img, t_point p, t_vars *v);

void				convertpoint(t_vars *vars, t_point *b, t_point a);
void				inittrigo(t_vars *vars);

int					getcolorpix(t_vars *v, char *addr, size_t k);
int					getindex(t_vars *v, int *i, t_map *tmp);

void				topdown(t_vars *v, t_map *tmp, int prevw, int prevh);
void				displaytopdown(t_vars *v);
// void		isometric(t_vars *v, t_map *tmp);

void				rendermenu(t_vars *v);

// Animations
void				animations(t_vars *v);
// void				playeranim(t_vars *v, int i);
// void				guardanim(t_vars *v, t_point p);
// void				objanim(t_vars *v, int i);
// void				puttexturesanim(t_vars *v, t_point i, t_point p,
// 						t_point d);

// Scenes

int					win(t_vars *v);
int					lose(t_vars *v);
void				loading(t_vars *v);
int					credits(t_vars *v);
int					maintitleanim(t_vars *v);

// Collisions
// int					checkcollisionsprojectiles(t_vars *v, t_point dir);
// int					checkhitmonster(t_vars *v, t_point p);
// void				iscollected(t_vars *v, int i, int ent, t_point p);

// Movements

void				move(t_vars *v, int d);
void				rotatecamx(t_vars *v, int d, double speed);
void				rotatecamy(t_vars *v, int d, double speed, int mul);
void				set_pos(t_vars *v, t_point2 k);
// void				attack(t_vars *v);

#endif