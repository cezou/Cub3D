
#include "../../includes/cub3D.h"

void	perr(const char *s)
{
	ft_printf(STDERR, "%sError\n%s%s%s\n", RED, LIL_RED, s, RCOLOR);
}

void	merr(const char *s)
{
	ft_printf(STDERR, "%sError\nMap: %s%s%s%s\n", RED, RCOLOR, LIL_RED, s,
		RCOLOR);
}

void	lerr(size_t i, const char *s)
{
	ft_printf(STDERR, "%sError\nLine %s%u%s: %s%s%s%s\n", RED, YELLOW, i, RED,
		RCOLOR, LIL_RED, s, RCOLOR);
}

int	cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	tab_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		;
	return (i);
}

// t_imgc	*init_xpm(const char *path, t_vars *v)
// {
// 	t_imgc *image;
// 	int trash;

// 	image = malloc(sizeof(t_imgc));
// 	if (!image)
// 		exit((prterr(v, ERRMALL, 1, 1), 1));
// 	image->img = mlx_xpm_file_to_image(v->mlx, path, &image->width,
// 			&image->height);
// 	if (!image->img)
// 		exit((free(image), prterr(&v, ERRMALL, 1, 1), 1));
// 	image->pixels = (t_color *)(t_hexa *)mlx_get_data_addr(image->img, &trash,
// 			&trash, &trash);
// 	return (image);
// }