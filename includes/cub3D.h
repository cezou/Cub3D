/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:08:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/25 17:20:30 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _XOPEN_SOURCE 600
# include "mlx_linux/minilibx-linux/mlx.h"
# include "mlx_linux/minilibx-linux/mlx_int.h"
# include "printf/ft_printf.h"
# include "uthash.h"
# include <X11/extensions/Xfixes.h>
# include <X11/keysym.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define FAIL EXIT_FAILURE
# define SUCCESS EXIT_SUCCESS
# define STDERR STDERR_FILENO

# define M_PI 3.14159265358979323846 /* pi */
# define WHITESPACES " \t\n\v\f\r"
# define MAX_KEYS 65535
# define MAX_MOUSE 8
# define SCROLL_UP 4
# define SCROLL_DOWN 5

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

# define THREAD_COUNT 20

// Sounds

# ifndef MANDATORY
#  define ACTIVATE_SOUND 0
#  define MANDATORY 0
#  define VALID " \t\n\v\f\r10NSWEDG"
# else
#  define ACTIVATE_SOUND 0
#  define MANDATORY 1
#  define VALID " \t\n\v\f\r10NSWE"
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
# define RE_P 0xFF0000
# define W_P 0xFFFFFF
# define GR_P 0x777777

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
# define ECEIL "Ceil: Need 4 coordinates (topleft[x,y] and botright[x,y] drawing a rectangle)"

// Resolutions

// # define XSET_0 "xset r rate 500 33"
// # define XSET_1 "xset r rate 100 12"
// # define XSET_2 "xset r rate 100 33"
// # define XSET_3 "xset r rate 500 12"
# define XSET_0 ""
# define XSET_1 ""
# define XSET_2 ""
# define XSET_3 ""
# define K_2 ""
# define W_H 600
# define W_W 800
// # define W_H		1080
// # define W_W		1920

# define TOOLBAR_LINUX_H 70

# define SKYBOX_REPEATS 4

# define FOGL 2
# define FOGC 0x000000

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

# ifndef WSL
#  define WSL 0
// #  define FONT1 "-sony-fixed-medium-r-normal--17-120-100-100-c-0-iso8859-1"
// #  define FONT2 "-sony-fixed-medium-r-normal--24-230-75-75-c-0-iso8859-1"
#  define FONT1 \
	"-misc-fixed-medium-r-semicondensed\
--13-120-75-75-c-60-iso8859-1"
#  define FONT2 \
	"-misc-fixed-medium-r-semicondensed\
--13-120-75-75-c-60-iso8859-1"
# else
#  define WSL 1
#  define FONT1 \
	"-misc-fixed-medium-r-semicondensed\
--13-120-75-75-c-60-iso8859-1"
#  define FONT2 \
	"-misc-fixed-medium-r-semicondensed\
--13-120-75-75-c-60-iso8859-1"
# endif
// # define FONT2 "-sun-open look glyph-----19-190-75-75-p-154-sunolglyph-1"

// Mr. Potato-Head by Joan Stark
# define POTATO \
	"\
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

# define CUB3D \
	"\
 _____  _   _ ______  _____ ______ \n\
/  __ \\| | | || ___ \\|____ ||  _  \\ \n\
| /  \\/| | | || |_/ /    / /| | | |\n\
| |    | | | || ___ \\    \\ \\| | | |\n\
| \\__/\\| |_| || |_/ /.___/ /| |/ / \n\
 \\____/ \\___/ \\____/ \\____/ |___/  \n"

# define BONUS \
	"\
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

# define SOUND_GENERIC "resources/sounds/1-01. Main Menu.mp3"
# define SOUND_FOOTSTEPWALK \
	"resources/sounds/Horror/\
Character/Footsteps_walking.wav"
# define SOUND_AMBIENT "resources/sounds/03.E1M1-AtDoomsGate.mp3"
# define SOUND_BABYLAUGH1 \
	"resources/sounds/Horror\
/Monsters & Ghosts/Child laugh_6.wav"
# define SOUND_BABYLAUGH2 \
	"resources/sounds/Horror\
/Monsters & Ghosts/Child laugh.wav"
# define SOUND_BABYLAUGH3 \
	"resources/sounds/Horror\
/Monsters & Ghosts/Child laugh_7.wav"
# define SOUND_BUTTONCLICK1 \
	"resources/sounds/Horror\
/House & Office/Can_clink_4.wav"
# define SOUND_BUTTONCLICK2 \
	"resources/sounds/Horror\
/House & Office/switch3.wav"
# define SOUND_GUARDINJURED \
	"resources/sounds/Horror\
/Monsters & Ghosts/Zombie.wav"
# define SOUND_GUARDDEATH \
	"resources/sounds/Horror\
/Monsters & Ghosts/Zombie_8.wav"
# define SOUND_ATTACK \
	"resources/sounds/Horror\
/Monsters & Ghosts/Injured.wav"
# define SOUND_CREDITS "resources/sounds/musics/wav/Ambient 2.wav"
# define SOUND_GAMEOVER "resources/sounds/musics/wav/Fx 3.wav"
# define SOUND_WIN "resources/sounds/musics/wav/Fx 1.wav"

# define GOTARMOR "Picked up the armor."
# define GOTMEGA "Picked up the MegaArmor!"
# define GOTHTHBONUS "Picked up a health bonus."
# define GOTARMBONUS "Picked up an armor bonus."
# define GOTSTIM "Picked up a stimpack."
# define GOTMEDINEED "Picked up a medikit that you REALLY need!"
# define GOTMEDIKIT "Picked up a medikit."
# define GOTSUPER "Supercharge!"

# define GOTBLUECARD "Picked up a blue keycard."
# define GOTYELWCARD "Picked up a yellow keycard."
# define GOTREDCARD "Picked up a red keycard."
# define GOTBLUESKUL "Picked up a blue skull key."
# define GOTYELWSKUL "Picked up a yellow skull key."
# define GOTREDSKULL "Picked up a red skull key."

# define GOTINVUL "Invulnerability!"
# define GOTBERSERK "Berserk!"
# define GOTINVIS "Partial Invisibility"
# define GOTSUIT "Radiation Shielding Suit"
# define GOTMAP "Computer Area Map"
# define GOTVISOR "Light Amplification Visor"
# define GOTMSPHERE "MegaSphere!"

# define GOTCLIP "Picked up a clip."
# define GOTCLIPBOX "Picked up a box of bullets."
# define GOTROCKET "Picked up a rocket."
# define GOTROCKBOX "Picked up a box of rockets."
# define GOTCELL "Picked up an energy cell."
# define GOTCELLBOX "Picked up an energy cell pack."
# define GOTSHELLS "Picked up 4 shotgun shells."
# define GOTSHELLBOX "Picked up a box of shotgun shells."
# define GOTBACKPACK "Picked up a backpack full of ammo!"

# define GOTBFG9000 "You got the BFG9000!  Oh, yes."
# define GOTCHAINGUN "You got the chaingun!"
# define GOTCHAINSAW "A chainsaw!  Find some meat!"
# define GOTLAUNCHER "You got the rocket launcher!"
# define GOTPLASMA "You got the plasma gun!"
# define GOTSHOTGUN "You got the shotgun!"
# define GOTSHOTGUN2 "You got the super shotgun!"

# define MAXHEALTH 100

typedef enum s_card
{
	it_blueskull,
	it_yellowskull,
	it_redskull,
	it_bluecard,
	it_yellowcard,
	it_redcard,
	NUMCARDS
}							t_card;

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
}							t_soundl;

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
}							t_dir;

// ERUN,
// EDAMAGED,
// EPICKUP,
// EDIE,
typedef enum s_anim
{
	EWALK,
	EATTACK,
	ANIM_N
}							t_anim;

typedef enum s_guard_states
{
	EIDLE,
	EPATROL,
	ECHASE,
	EATTACKM,
	EATTACKR,
	EPAIN,
	EDEAD,
	ETRAVEL,
	EHIT
}							t_guard_states;

typedef enum s_door_state
{
	EOPEN,
	ECLOSE,
	EOPENING,
	ECLOSING
}							t_door_state;

typedef enum s_ammo
{
	EBULL,
	ESHELL,
	EROCK,
	ECELL,
	NUMAMMO,
	NOAMMO
}							t_ammo;

typedef enum s_weapons
{
	EFIST,
	EGUN,
	ESHOTGUN,
	EGATLIN,
	EROCKETL,
	EPLASMA,
	EBFG,
	ECHAINSAW,
	ESUPERSHOTGUN,
	NUMWEAPONS
}							t_weapons;

typedef enum s_components
{
	EMAP,
	ESOUTH,
	ENORTH,
	EWEST,
	EEAST,
	EMAPBORDER,
	EMAPHEAD,
	ESPACE,
	EDOOR,
	EGUARDW,
	EGUARDDEATH,
	EGUARDATTR,
	ESKYBOX,
	EHUDIMG,
	ETITLE,
	EKEK,
	EDOOMH,
	EBIGNUMBERSTMP,
	ESMALLNUMBERSTMP,
	EHEALTHTMP,
	EARMORTMP,
	EAMMOTMP,
	EWEAPONTMP,
	EAMMUNTMP,
	ECARDSLOTTMP,
	ECARDSTMP,
	EPARMOR,
	EPARMOR1,
	ESTIM,
	EMEDI,
	EPCLIP,
	EPSHELL,
	EPROCK,
	EPCELL,
	EBKEY,
	EYKEY,
	ERKEY,
	EBSKEY,
	EYSKEY,
	ERSKEY,
	EPBFG,
	EPSHOTGUN,
	EPGATLIN,
	EPROCKETL,
	EPPLASMA,
	EPCHAINSAW,
	EPSUPERSHOTGUN,
	EPLASMABOLT,
	EMENUSELECT,
	EMENU,
	EMENUIG,
	EMENUOPT,
	EBUFF,
	EHUD,
	EIFIST,
	EIGUN,
	EISHOTGUN,
	EIGATLIN,
	EIROCKl,
	EIPLASMA,
	EICHAINSAW,
	EISUPERSHOTGUN,
	EIBFG,
	EBIGNUMBERS,
	ESMALLNUMBERS,
	EHEALTH,
	EARMOR,
	EAMMO,
	EWEAPON,
	EAMMUN,
	ECARDSLOT,
	ECARDS,
	EDOOMHTMP,
	EHUDTMP,
	ETMP,
	COMP_N
}							t_comp;

typedef struct s_sprite_entry
{
	const char				*name;
	int						id;
}							t_sprite_entry;

typedef struct s_sprite_map
{
	const char				*key;
	int						value;
	UT_hash_handle			hh;
}							t_sprite_map;

int							get_sprite_id(t_sprite_map *map, const char *key);

typedef int					i;

typedef struct s_point
{
	int						x;
	int						y;
	int						z;
	int						color;
}							t_point;

typedef struct s_point2
{
	double					x;
	double					y;
	int						z;
	int						t;
}							t_point2;

typedef struct s_point3
{
	double					x;
	double					y;
	int						z;
	double					uv;
	double					v;
}							t_point3;

typedef struct s_point4
{
	double					x;
	double					y;
	double					vectorx;
	double					vectory;
	double					uv;
	double					v;
	int						img_id;
}							t_point4;

typedef struct s_obj
{
	double					x;
	double					y;
	int						img_id;
	double					uv;
	double					v;
	int						h;
	int						pickable;
}							t_obj;

typedef float t_v2f			__attribute__((vector_size(8)));
typedef unsigned int t_v2u	__attribute__((vector_size(8)));
typedef int t_v2i			__attribute__((vector_size(8)));

typedef struct s_map
{
	int						x;
	int						y;
	int						z;
	char					val;
	int						rev;
	struct s_map			*right;
	struct s_map			*left;
	struct s_map			*up;
	struct s_map			*down;
}							t_map;

/**
 * @struct s_cell
 * @brief Structure reprensenting a cell in the grid
 * @tparam	parent_i 	Row index of its parent, 0 <= i >= ROW-1
 * @tparam	parent_j 	Column index of its parent, 0 <= j >= COLUMN-1
 * @tparam	f 			Sum of g and h
 * @tparam	g 			Value of the movement cost from the starting
 * 	point to a given tile on the grid, following the generated path to get there
 * @tparam	h 			Value of the estimated movement cost to move
 * 	from that given tile to the target. Referred as "heuristic"
 */
typedef struct s_cell
{
	int						parent_i;
	int						parent_j;
	double					f;
	double					g;
	double					h;
}							t_cell;

/** @struct s_pathfinding
 *  @brief Open list having information as <f, <i, j>>
 *  where f = g + h,
 *  and i, j are the row and column index of that cell
 *  Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
 *  @tparam f 		Sum of g + h
 *  @tparam i 		Row index
 *  @tparam j 		Column index
 *  @tparam *next 	Next node in the linked list
 *  @tparam *prev 	Previous node in the linked list
 */
typedef struct s_pathfinding
{
	double					f;
	int						i;
	int						j;
	t_map					*curr;
	struct s_pathfinding	*next;
	struct s_pathfinding	*prev;
}							t_pathfinding;

/** @struct s_astar
 *  @brief Structure holding all the datas necessary for the
 *  pathfinding algorithm
 *  @tparam i 				Row index
 * 	@tparam j 				Column index
 * 	@tparam	finddst 		Boolean to inform if we found the destination
 * 	@tparam	gnew 			New value of the movement cost from the starting
 * 	point to a given tile on the grid, following the generated path to get there
 * 	@tparam	hnew 			New value of the estimated movement cost to move
 * 	from that given tile to the target. Referred as "heuristic"
 *	@tparam fnew 			New value of gnew + hnew
 *	@tparam	closedlst 		Boolean array representing cells that have already
 *	been tested
 *	@tparam	curr 			Reference to the current node in the map to test the
 *	position
 *	@tparam	target 			Reference to the target position in the map
 *	@tparam	celld 	Array holding the datas of the cells
 *	@tparam	tmp 			Reference of the node in the pathfinding linked list
 *	@tparam	del 			Reference to the node that will be delete in the
 *	pathfinding linked list
 *	@tparam	next 			Reference of the next node in the pathfinding linked
 *	list
 */
typedef struct s_astar
{
	int						i;
	int						j;
	int						nb_astar;
	bool					finddst;
	double					gnew;
	double					hnew;
	double					fnew;
	bool					**closedlst;
	t_map					*curr;
	t_map					*dir;
	t_map					*target;
	t_cell					**celld;
	t_pathfinding			*open;
	t_pathfinding			*trace;
	t_pathfinding			*del;
	t_pathfinding			*next;
}							t_astar;

typedef struct s_actor
{
	int						active;
	double					x;
	double					y;
	int						hp;
	int						dmg;
	int						hashitbox;
	int						justattack;
	int						hasrange;
	int						hasmelee;
	int						painchance;
	int						isguard;
	int						isprojectile;
	int						pickable;
	int						stop;
	int						state;
	int						img_i;
	int						xdelta;
	int						animoffx;
	int						animoffy;
	double					targetdist;
	double					norm;
	double					ms;
	double					vdiv;
	double					udiv;
	double					vmove;
	double					dist;
	double					vectorx;
	double					vectory;
	t_map					*map_pos;
	t_map					*target;
	uint64_t				timestate;
	uint64_t				time;
	struct s_actor			*prev;
	struct s_actor			*next;
	t_astar					astar;
}							t_actor;

typedef struct s_imga
{
	void					*img;
	struct s_imga			*anim;
	int						animnb;
	char					*addr;
	int						bpp;
	int						len;
	int						endian;
	int						width;
	int						height;
	char					*filename;
	char					*fontname;
	char					*fontname2;
	int						animx;
	int						animy;
	int						id;
	double					ratiox;
	double					ratioy;
}							t_imga;

typedef struct s_door
{
	int						x;
	int						y;
	int						img_i;
	t_door_state			state;
	uint64_t				time;
	int						xdelta;
}							t_door;

typedef struct s_ray
{
	int						x;
	int						hitguard;
	double					camera_x;
	double					dir_x;
	double					dir_y;
	double					dir_x1;
	double					dir_y1;
	int						map_x;
	int						map_y;
	int						step_x;
	int						step_y;
	double					pos;
	double					step;
	double					sidedist_x;
	double					sidedist_y;
	double					deltadist_x;
	double					deltadist_y;
	double					wall_dist;
	double					wall_x;
	int						side;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						pitch;
	int						tx0;
	int						tx1;
	int						dtx;
	int						dy;
	int						dty;
	int						ty0;
	int						hitside;
	double					hitx;
	double					centerdist;
	t_map					*hit;
	t_map					*centerhit;
	t_imga					img;
	t_door					door;
	int						lim;
	int						*zbuffer;
}							t_ray;

typedef struct s_sprite_data
{
	int						drawstartx;
	int						drawstarty;
	int						drawendx;
	int						drawendy;
	int						spritescreenx;
	int						vmovescreen;
	int						spritewidth;
	int						spriteheight;
	double					transformy;
}							t_sprite_data;

typedef struct s_floor
{
	double					dir_x;
	double					dir_x1;
	double					dir_y;
	double					dir_y1;
	double					fstepx;
	double					fstepy;
	double					fx;
	double					fy;
	double					rowdist;
	int						tx;
	int						ty;
	int						tx1;
	int						ty1;
	int						cx;
	int						cy;
	int						dcx;
	int						dcy;
	int						lim;
	int						t[2];
	bool					isfloor;
}							t_floor;

typedef struct s_trig
{
	double					cosx;
	double					sinx;
	double					cosy;
	double					siny;
	double					cosz;
	double					sinz;
}							t_trig;

typedef struct s_mouse
{
	int						button;
	int						prevx;
	int						prevy;
	int						renderrate;
	long double				zoom;
	long double				xoff;
	long double				yoff;
	double					xangle;
	double					yangle;
	double					zangle;
	float					zheight;
	double					sensx;
	double					sensy;
}							t_mouse;

typedef struct s_sound
{
	ma_result				result;
	ma_engine				engine;
	ma_sound				sound[SOUND_NB];
	ma_context				context;
	ma_device_config		deviceconfig;
	float					volume;
	int						init;
}							t_sound;

typedef struct s_weapon
{
	int						active;
	int						ammo;
	int						maxammo;
	u_int8_t				typeammo;
	int						dmg;
	int						idsound;
	int						isprojectile;
	int						dmgtic;
	double					range;
	t_imga					img;
}							t_weapon;

typedef struct s_player
{
	t_map					*player;
	int						pattack;
	int						attack;
	int						animp;
	int						animoff;
	int						moving;
	int						movingy;
	int						jumping;
	int						injump;
	int						dir;
	int						hp;
	int						hit;
	int						armor;
	int						armortype;
	int						ammo[4];
	int						maxammo[4];
	int						clipammo[4];
	int						weapons[NUMWEAPONS];
	int						cards[3];
	t_weapon				currweapon;
	t_weapon				weapon[NUMWEAPONS];
	double					x;
	double					y;
	double					z;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
	double					angle;
	double					motionx;
	double					motiony;
	double					accx;
	double					accy;
	double					deccx;
	double					deccy;
	double					maxspeedx;
	double					maxspeedy;
	double					movespeedx;
	double					movespeedy;
	double					rotspeed;
	double					mouserotspeed;
	uint64_t				timerplayer;
}							t_player;

typedef struct s_hud
{
	bool					refresh;
	bool					refreshfps;
	bool					refreshdh;
	bool					refreshhealth;
	bool					refresharmor;
	bool					refreshammo;
	bool					refreshammun;
	bool					refreshweapon;
	bool					refreshcards;
	t_imga					img;
	t_imga					head;
	int						headid;
	int						animoff;
	size_t					map_zoom;
	uint64_t				time;
}							t_hud;

typedef struct s_mapv
{
	t_map					*map;
	int						mapvalid;
	int						error;
	int						mapw;
	int						maph;
	int						tmpx;
	int						tmpy;
	int						resdeltax;
	int						resdeltay;
	int						shiftx;
	int						shifty;
	char					*filename;
}							t_mapv;

typedef struct s_menu
{
	int						menui;
	int						menu;
}							t_menu;

typedef struct s_screen
{
	t_win_list				*win;
	long					resw;
	long					resh;
	int						screenw;
	int						screenh;
	int						gamew;
	int						gameh;
	int						hudw;
	int						hudh;
	double					ratio;
}							t_screen;

typedef struct s_game
{
	int						pause;
	int						pain;
	int						start;
	int						fps;
	uint64_t				created_at;
	uint64_t				updated_at;
	double					cambobtime;
	double					playbobtime;
	double					frametime;
	uint64_t				time;
	uint64_t				oldtime;
	double					doortime;
	int						won;
	int						god;
	t_imga					skybox;
	int						nb_door;
	int						nb_guard;
	int						nb_actors;
	int						canhit;
	char					*message;
}							t_game;

typedef struct s_boolimage
{
	bool					is_set;
	t_imga					imga;
}							t_boolimage;

typedef struct s_infos
{
	char					**map;
	size_t					map_index;
	size_t					map_height;

	t_boolimage				north;
	t_boolimage				south;
	t_boolimage				east;
	t_boolimage				west;

	bool					f;
	bool					c;
	bool					player;
	uint32_t				ceil;
	uint32_t				floor;

	t_v2i					ceil_topleft;
	t_v2i					ceil_botright;

}							t_infos;

typedef struct s_thread_pool
{
	int						thread_count;
	pthread_t				*threads;
	pthread_barrier_t		tbarrier;
	pthread_barrier_t		mbarrier;
	pthread_mutex_t			job_mutex;
	pthread_cond_t			job_cond;
	int						work_available;
	volatile int			stop;
}							t_thread_pool;

// Structure to hold each thread's datat
typedef struct s_thread_data
{
	struct s_vars			*v;
	int						thread_id;
	int						start;
	int						end;
	t_thread_pool			*pool;
	t_floor					f;
	int						job;
	t_imga					tmp[2];
	pthread_mutex_t			data_mutex;
}							t_thread_data;

typedef struct s_vars
{
	t_infos					infos;
	t_obj					g_objs[200];
	int						num_objs;
	t_sprite_entry			entries[COMP_N];
	t_sprite_map			*sprite_map;

	t_xvar					*mlx;
	bool					keys[MAX_KEYS];
	bool					mouses[MAX_MOUSE];
	Cursor					cursor;
	Pixmap					blank;
	t_actor					*actors;
	t_imga					*img;
	t_mouse					mouse;
	t_map					*last;
	t_trig					trig;
	t_sound					sound;
	t_game					game;
	t_screen				screen;
	t_menu					menu;
	t_door					*door;
	t_mapv					mapv;
	t_player				player;
	t_ray					ray;
	t_sprite_data			sp;
	t_floor					floor;
	t_hud					hud;
	t_imga					tmp[2];
	int						*rand;
	int						rndindex;
	int						prndindex;
	uint32_t				tex[8][4160];
	t_thread_pool			pool;
	t_thread_data			threads_data[THREAD_COUNT];
	int						frame;
	int						exit;
}							t_vars;

// Parsing
int							cmp(const char *s1, const char *s2);

// Utils
void						showparams(t_vars *v);
int							parse(t_vars *vars, int j, t_map *p);
int							flood_fill(t_vars *v, t_map **tmp, int *i);
t_map						*new_point(t_vars *v, char val, t_map **p);
void						add_element(t_map **vars, t_map **node, t_map **tmp,
								t_map **left);
int							printmap(t_vars *vars, int i);
int							printmap2(t_vars *v);
void						prterr(t_vars *v, char *err, int cleardatab,
								int init);
void						perr(const char *s);
void						merr(const char *s);
int							myrand(int nb);
t_point2					get_90_angle(int dir, double x, double y);
float						deg_to_rad(float deg);
float						rad_to_deg(float rad);
int							find_door(t_vars *v, int x, int y);
int							find_guard(t_vars *v, t_map *tmp);
void						hitguard(t_vars *v, t_sprite_data *sp, t_actor *g);
void						guardattack(t_vars *v, t_sprite_data *sp,
								t_actor *g);
int							m_random(t_vars *v);
int							p_random(t_vars *v);
void						m_clearrandom(t_vars *v);
void						save_screen_to_buffer(t_imga dest, t_imga src,
								size_t offset);
t_actor						*new_actor(t_vars *v);
void						add_actor(t_vars *v, t_actor **actors,
								t_actor **node);
void						add_cell(t_astar *astar, t_pathfinding **node,
								t_pathfinding **lst);
t_pathfinding				*new_cell(double f, int i, int j, t_map *dir);
int							printactors(t_vars *v);
void						sort_descending(t_actor **head, int bound,
								bool swapped, t_actor *last_sorted);
void						ft_swaps(t_actor **head, t_actor *a, t_actor *b);

// Interactions

void						touch_thing(t_vars *v, t_actor *a);
bool						give_weapon(t_vars *v, t_weapons weapon,
								char *mess);
bool						give_ammo(t_vars *v, int img, int num, t_ammo ammo);
bool						give_armor(t_vars *v, t_actor *a);
bool						give_body(t_vars *v, int num, int sp);
bool						give_cards(t_vars *v, t_actor *a);
void						fire_projectile(t_vars *v);
void						apply_damage(t_vars *v, t_actor *g);

// Time

uint64_t					timestamp_in_ms(t_vars *v);
void						scrolling(t_vars *v, float *h, char *str,
								t_point2 p);
// int			timer(int delay);

// Clear
int							clearimgs(t_vars *v);
int							freeall(char **tab);
int							cleardata(t_vars *vars, int b);
int							map_clear(t_map *lst);
int							actors_clear(t_actor *lst);
int							booltab_clear(bool **tab);
int							cells_clear(t_cell **tab);
void						stop_threads_pool(t_vars *v);

// Init
void						init(t_vars *v, int argc, char **argv);
void						check_map(t_vars *v);
void						inittextures(t_vars *v, int i);
void						inittexture(t_vars *v, t_imga *img, int i);
void						initplayeranim(t_vars *v);
void						initobjectsanim(t_vars *v, int i, int obj);
void						initguardanim(t_vars *v);
void						init_cam(t_vars *vars);
void						initmodes(t_vars *v, int argc);
void						initsounds(t_vars *v);
void						initimage(t_vars *v, int index, int width,
								int height);
void						initvars(t_vars *v);
void						initwindow(t_vars *v, int argc, char **argv);
void						initpathtext(t_vars *v);
void						initplayerpathanim(t_vars *v);
void						initguardpathanim(t_vars *v);
// void						initprojectilepathanim(t_vars *v);
void						inithud(t_vars *v);
void						init_player_dir(t_vars *v);
void						init_random_melting_array(t_vars *v);
void						initanim(t_vars *v, int index, int b, int animnb);
void						mouse_hide(t_vars *v);

// Mouse

int							mouse_up(int button, int x, int y, t_vars *p);
int							mouse_down(int button, int x, int y, t_vars *p);
void						zoom(int button, t_vars *vars);
int							mouse_move(int x, int y, t_vars *p);

// Closing / Hooks

int							keys(int keycode, t_vars *vars);
int							closecross(t_vars *vars);
void						hooks(t_vars *vars);
void						hotreload(t_vars *vars);
int							keys_release(int keycode, t_vars *v);
void						menuexit(t_vars *v);
void						menuarrow(t_vars *v, int d);
void						menuoptions(t_vars *v);
void						attack(t_vars *v, int kd);

// Controls

void						move(t_vars *v);
void						moveplayerx(t_vars *v, int d);
void						moveplayery(t_vars *v, int d);
void						rotatecamx(t_vars *v, int d, double speed);
void						rotatecamy(t_vars *v, int d, double speed, int mul);
t_map						*set_pos(t_vars *v, t_point2 k, t_map *m, int d);
t_map						*set_pos_guards(t_vars *v, t_point2 k, t_map *m,
								t_actor *a);
bool						can_move(t_vars *v, t_point2 p, t_actor *tmp,
								t_actor *actor);
void						open_door(t_vars *v);

// Rendering

int							raycasting(t_vars *v, t_imga dest);
void						set_dda(t_vars *v);
void						perform_dda(t_vars *v, t_map *tmp, int hit);
void						dda_utils(t_vars *v);
void						calculate_line_height(t_vars *v);

void						check_door(t_vars *v);
int							door_extend_ray(t_vars *v, t_point p, int *t);
void						update_texture_pixels(t_vars *v, t_point p, int *t);

// Pathfinding

bool						astar(t_vars *v, t_astar *astar);

// Threading

void						*job(void *v);
void						draw_floor_ceiling_threaded(t_vars *v, t_imga dest);
void						add_pix_custom(t_vars *v, t_point p, t_point3 fog,
								t_imga *tmp);
void						draw_skybox_threaded(t_vars *v, t_imga dest);

// Animations
void						update_door_animations(t_vars *v, int i);
void						update_actors(t_vars *v);
void						update_player(t_vars *v);
void						update_guards(t_vars *v, t_actor **actor);
t_actor						*update_projectiles(t_vars *v, t_actor **actor,
								int *i);

void						draw_floor_ceiling(t_vars *v);
void						init_data_floor(t_vars *v, t_floor *f, int y);
void						update_floor_ceil_texture_pixels(t_vars *v,
								t_floor *f, t_point p, t_imga *tmp);

void						draw_sprites(t_vars *v);
void						draw_sprite(t_vars *v, t_sprite_data *sp,
								t_actor *g, t_point p);
void						transform_sprite(t_vars *v, t_sprite_data *sp,
								t_actor *g);
void						set_sprite_boundaries(t_vars *v, t_sprite_data *sp,
								t_actor *g);
void						sort_sprites(t_vars *v);

void						draw_skybox(t_vars *v, t_point p, t_floor *f);
void						set_skybox(t_vars *v, t_floor *f, int w, int xs);
void						surf_rows(t_vars *v, t_point p, t_floor *f,
								t_imga *tmp);

// HUD

void						renderhud(t_vars *v, t_imga dest);
void						renderelement(t_vars *v, int xoff, int nb,
								int percent);
void						number_to_digits(t_vars *v, int n, int res[4],
								int *i);
void						renderarmsdigits(t_vars *v, int xoff);
void						rendersmalldigit(t_vars *v, int res[4], t_point g,
								int yoff);
void						renderammun(t_vars *v, int xoff, int arr[4]);
void						rendercards(t_vars *v, int xoff, int yoff,
								int *arr);
void						render_fps(t_vars *v, double fps);

void						render_player(t_vars *v, t_point c);

void						scale_img(t_point p, t_imga *src, t_imga *dest);

int							render(t_vars *data);
void						img_pix_put(t_imga *img, t_point p, t_vars *v);
void						add_pix(t_vars *v, t_point p, t_point3 fog,
								t_point opt);
void						create_textures(t_vars *v, t_point c);
int							getcolorpix(t_vars *v, char *addr, size_t k);
uint32_t					color_lerp(uint32_t color1, uint32_t color2,
								double t);

void						rendermenu(t_vars *v);

// Animations
void						update_animations(t_vars *v);

// Scenes

int							win(t_vars *v);
int							lose(t_vars *v);
int							transition_melt_screen(t_vars *v);
int							credits(t_vars *v);
int							maintitleanim(t_vars *v);
void						melting(t_vars *v, bool *done, int x);

/* FUNCTIONS */
void						free_sprite_map(t_sprite_map **map);
t_sprite_entry				*create_entries(void);
void						free_sprite_map(t_sprite_map **map);
void						print_sprite_map(t_sprite_map *map);
void						init_sprite_map(t_vars *v, t_sprite_map **map);
void						store_an_obj(char **l, int line, int fd, t_vars *v);
void						eerr(const char *s, int i);
int							get_sprite_id(t_sprite_map *map, const char *key);
void						parsing_csv(char *filename, t_vars *v);
void						eerr(const char *s, int i);
bool						isnt_ended_by(const char *s, const char *ext);
size_t						len(const char *s);
char						*dupspace(char *s);
char						*skip_whitespaces(t_vars *v, int fd, int *i);
void						calculate_mapsize_checking(char *line, t_vars *v,
								int fd, int i);
bool						is_there_unclosed_doors(char **map, t_vars *v);

void						draw_square(t_v2f pos, float size, int color,
								t_vars *v);
void						draw_rotated_img(t_imga *img, t_v2f pos, float size,
								t_vars *v, float angle);
void						draw_scaled_img(t_imga *img, t_v2f pos, float size,
								t_vars *v);
;
void						rendermap(t_vars *v);
// void					freeall(void **tab);
void						key_management(t_vars *v);
int							returnkey(t_vars *v);
void						handle_movement(t_vars *v);
bool						is_pressed(int key, t_vars *v);
bool						is_in_string(char c, char *s);
bool						is_surrounded(char **map, int i, int j,
								size_t map_start);
char						**tab_dup(char **tab);
void						init_infos(t_vars *v, char *file, int *fd);
bool						is_map_closed(char **map, size_t map_start);
bool						is_not_accepted(char **map, int i, int j);
void						print_map(char **s);
bool						is_in_string(char c, char *s);
void						cerr(int i, int j);

void						store_map(t_vars *v, int fd, int i);
void						s(void);

bool						is_char_valid(char c);
bool						is_player_char(char c);
bool						isnt_cub_ended(const char *s);
bool						there_is_only_whitespaces(const char *s);
bool						there_is_only_whitespaces(const char *s);
int							init_xpm(t_imga *img, char *path, void *mlx, int i);
size_t						nb_occur(const char *s, char c);
bool						is_color(char *s);
bool						is_texture(char *s);
bool						is_everything_set(t_infos i);
int							set_value(t_boolimage *bimg, char *file, void *mlx,
								int i);
int							set_texture(t_infos *i, char **l, int ind,
								void *mlx);
int							set_a_color(int i, char *values, uint32_t *color,
								bool *is_set);
int							set_colors(t_infos *i, char **l, int ind);
int							set_a_value(t_infos *i, char **l, int ind,
								void *mlx);
void						init_imgs(t_vars *v);
void						clean_exit(char **l, int fd, t_vars *v,
								bool free_line);
void						pfree_img(t_imga *img, t_vars *v);
char						*strrev(char *s);
bool						is_valid_int(const char *s);
bool						is_valid_int(const char *s);
void						parsing(int ac, char *filename, t_vars *v);
bool						isnt_cub_ended(const char *s);

void						lerr(size_t i, const char *s);
size_t						tab_len(char **tab);
int							cmp(const char *s1, const char *s2);

#endif