/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/28 13:44:48 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	cmpalpha(const void *const a, const void *const b)
{
	return (ft_strncmp((*(struct dirent **)a)->d_name,
			(*(struct dirent **)b)->d_name,
			ft_strlen((*(struct dirent **)b)->d_name)));
}

bool	load_file(t_vars *v, DIR *fd, struct dirent **f, const char *dir)
{
	static int (i) = -1;
	if (!ft_strncmp((*f)->d_name, ".", 1) || !ft_strncmp((*f)->d_name, "..", 2)
		|| ft_strncmp((*f)->d_name + (ft_strlen((*f)->d_name) - 4), ".xpm", 4))
		return (*f = readdir(fd), false);
	v->img[ESKYBOX].anim[++i].filename = ft_calloc(ft_strlen(dir)
			+ ft_strlen((*f)->d_name) + 2, sizeof(char));
	if (!v->img[ESKYBOX].anim[i].filename)
		exit((prterr((closedir(fd), v), ERRMALL, 1, 1), 1));
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, dir, ft_strlen(dir) + 1);
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, "/",
		ft_strlen(v->img[ESKYBOX].anim[i].filename) + 2);
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, (*f)->d_name,
		ft_strlen(v->img[ESKYBOX].anim[i].filename)
		+ ft_strlen((*f)->d_name) + 1);
	ft_printf(1, "Procession file: %s\n", v->img[ESKYBOX].anim[i].filename);
	int (file) = open(v->img[ESKYBOX].anim[i].filename, O_RDONLY);
	if (file == -1)
		exit((prterr((closedir(fd), v),
					"Error : Failed to open entry file\n", 1, 1), 1));
	inittexture(v, &v->img[ESKYBOX].anim[i], i);
	*f = readdir(fd);
	if (close(file) == -1)
		exit((prterr((closedir(fd), v), "Error : Close file\n\n", 1, 1), 1));
	v->img[ESKYBOX].animnb = i;
	return (true);
}

void	load_images_from_folder(t_vars *v, const char *dir)
{
	DIR				*fd;
	struct dirent	*in_file;
	struct dirent	**lst;
	int				i;

	i = 1;
	if (MANDATORY)
		return ;
	fd = opendir(dir);
	if (!fd)
		exit((prterr(v, "Error : Failed to open input directory\n", 1, 1), 1));
	in_file = readdir(fd);
	while (in_file)
	{
		in_file = readdir(fd);
		++i;
	}
	lst = malloc(sizeof(*lst) * i);
	if (!lst)
		exit((prterr((closedir(fd), v), ERRMALL, 1, 1), 1));
	v->img[ESKYBOX].anim = ft_calloc(i, sizeof(t_imga));
	if (!v->img[ESKYBOX].anim)
		exit((prterr((free(lst), closedir(fd), v), ERRMALL, 1, 1), 1));
	rewinddir(fd);
	i = -1;
	in_file = readdir(fd);
	while (in_file)
	{
		lst[++i] = in_file;
		in_file = readdir(fd);
	}
	qsort(lst, i, sizeof(*lst), cmpalpha);
	free(lst);
	rewinddir(fd);
	in_file = readdir(fd);
	ft_printf(1, "Opening dir: %s\n", dir);
	while (in_file)
	{
		if (!load_file(v, fd, &in_file, dir))
			continue ;
	}
	if (closedir(fd) == -1)
		exit((prterr((closedir(fd), v),
					"Error : Close dir\n\n", 1, 1), 1));
}

void	initpath2(t_vars *v)
{
	v->img[ESPACE].filename = "resources/textures/Concrete_square_grey.xpm";
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EHANGCORPSE01].filename = "resources/textures/hang_corpse01.xpm";
	v->img[EHANGCORPSE02].filename = "resources/textures/hang_corpse02.xpm";
	v->img[EHANGCORPSE03].filename = "resources/textures/hang_corpse03.xpm";
	v->img[EFIRELAMP01].filename = "resources/textures/fire_lamp01.xpm";
	v->img[EPARMOR].filename = "resources/textures/armor.xpm";
	v->img[EPARMOR1].filename = "resources/textures/armor1.xpm";
	v->img[ESTIM].filename = "resources/textures/stimpack.xpm";
	v->img[EMEDI].filename = "resources/textures/medikit.xpm";
	v->img[EPCLIP].filename = "resources/textures/clip.xpm";
	v->img[EPSHELL].filename = "resources/textures/shells.xpm";
	v->img[EPROCK].filename = "resources/textures/rocket.xpm";
	v->img[EPCELL].filename = "resources/textures/cells.xpm";
	v->img[EBKEY].filename = "resources/textures/bluekey.xpm";
	v->img[EBSKEY].filename = "resources/textures/blueskull.xpm";
	v->img[EYKEY].filename = "resources/textures/yellowkey.xpm";
	v->img[EYSKEY].filename = "resources/textures/yellowskull.xpm";
	v->img[ERKEY].filename = "resources/textures/redkey.xpm";
	v->img[ERSKEY].filename = "resources/textures/redskull.xpm";
	v->img[EGUARDW].filename = "resources/textures/monster_walk.xpm";
	v->img[EGUARDDEATH].filename = "resources/textures/generaldeath.xpm";
	v->img[EGUARDATTR].filename = "resources/textures/generalattackrange.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUDempty.xpm";
	v->img[EMAPBORDER].filename = "resources/textures/MapBorder.xpm";
	v->img[EMAPHEAD].filename = "resources/textures/MapHead.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
	load_images_from_folder(v, "resources/textures/Animated_SkyBox/SkyBox3");
}

// v->img[EGUARDW].filename = "resources/textures/general.xpm";

void	initpathtext(t_vars *v)
{
	initpath2(v);
	v->img[EMENUSELECT].filename = "resources/textures/menus/select.xpm";
	v->img[EMENU].filename = "resources/textures/menus/menu_start.xpm";
	v->img[EMENUIG].filename = "resources/textures/menus/menu_ingame.xpm";
	v->img[EMENUOPT].filename = "resources/textures/menus/menu_options.xpm";
	v->img[EKEK].filename = "resources/textures/DoomTitle.xpm";
	v->img[EDOOMH].filename = "resources/textures/Doomhead.xpm";
	v->img[EBIGNUMBERSTMP].filename = "resources/textures/BigRedNumbers.xpm";
	v->img[ESMALLNUMBERSTMP].filename = "resources/textures/SmallNumbers.xpm";
	v->img[EHEALTHTMP].filename = "resources/textures/Health.xpm";
	v->img[EARMORTMP].filename = "resources/textures/Armor.xpm";
	v->img[EAMMOTMP].filename = "resources/textures/Ammo.xpm";
	v->img[EWEAPONTMP].filename = "resources/textures/Arms.xpm";
	v->img[EAMMUNTMP].filename = "resources/textures/Ammunitions.xpm";
	v->img[ECARDSTMP].filename = "resources/textures/Cards.xpm";
	v->img[ECARDSLOTTMP].filename = "resources/textures/CardsSlot.xpm";
	v->img[EPBFG].filename = "resources/textures/pbfg.xpm";
	v->img[EPSHOTGUN].filename = "resources/textures/pshotgun.xpm";
	v->img[EPGATLIN].filename = "resources/textures/pgatlin.xpm";
	v->img[EPROCKETL].filename = "resources/textures/procketl.xpm";
	v->img[EPPLASMA].filename = "resources/textures/pplasma.xpm";
	v->img[EPCHAINSAW].filename = "resources/textures/pchainsaw.xpm";
	v->img[EPSUPERSHOTGUN].filename = "resources/textures/psupershotgun.xpm";
	v->img[EPLASMABOLT].filename = "resources/textures/plasmabolt.xpm";
}

void	initanim(t_vars *v, int index, int b, int animnb)
{
	double	factorx;
	double	factory;
	double	scalefactor;

	factorx = (double)v->screen.gamew / 800;
	factory = (double)v->screen.gameh / 600;
	scalefactor = factorx;
	if (factorx >= factory)
		scalefactor = factory;
	v->img[ETMP].filename = v->img[index].filename;
	inittexture(v, &v->img[ETMP], ETMP);
	v->img[index].width = scalefactor * v->img[ETMP].width * 3;
	v->img[index].height = scalefactor * v->img[ETMP].height * 3;
	initimage(v, index, v->img[index].width, v->img[index].height);
	scale_img((t_point){0}, &v->img[ETMP], &v->img[index]);
	v->img[index].animx = v->img[ETMP].width / animnb * (1.0
			/ v->img[index].ratiox);
	v->img[index].animy = v->img[index].height;
	if (b)
		mlx_destroy_image(v->mlx, v->img[ETMP].img);
}

void	initplayerpathanim(t_vars *v)
{
	v->img[EIFIST].filename = "resources/textures/fist.xpm";
	initanim(v, EIFIST, 1, 7);
	v->player.currweapon.img = v->img[EIFIST];
	v->img[EIGUN].filename = "resources/textures/gun.xpm";
	initanim(v, EIGUN, 1, 7);
	v->img[EISHOTGUN].filename = "resources/textures/shotgun.xpm";
	initanim(v, EISHOTGUN, 1, 8);
	v->img[EIGATLIN].filename = "resources/textures/gatlin.xpm";
	initanim(v, EIGATLIN, 1, 3);
	v->img[EIROCKl].filename = "resources/textures/rocketl.xpm";
	initanim(v, EIROCKl, 1, 6);
	v->img[EIPLASMA].filename = "resources/textures/plasma.xpm";
	initanim(v, EIPLASMA, 1, 4);
	v->img[EICHAINSAW].filename = "resources/textures/chainsaw.xpm";
	initanim(v, EICHAINSAW, 1, 4);
	v->img[EISUPERSHOTGUN].filename = "resources/textures/supershotgun.xpm";
	initanim(v, EISUPERSHOTGUN, 1, 10);
	v->img[EIBFG].filename = "resources/textures/bfg.xpm";
	initanim(v, EIBFG, 0, 4);
}

void	initguardpathanim(t_vars *v)
{
	// v->img[EGUARDW].animx = v->img[EGUARDW].width / 4;
	v->img[EGUARDW].animy = v->img[EGUARDW].height / 4;
	v->img[EGUARDW].animx = v->img[EGUARDW].width / 8;
	v->img[EGUARDDEATH].animx = v->img[EGUARDDEATH].width / 4;
	v->img[EGUARDATTR].animx = v->img[EGUARDATTR].width / 4;
	v->img[EPLASMABOLT].animx = v->img[EPLASMABOLT].width / 7;
	v->img[EPLASMABOLT].animy = v->img[EPLASMABOLT].height;
}

// void	initprojectilepathanim(t_vars *v)
// {
// 	(void)v;
// }
