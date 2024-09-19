
#include "../../includes/cub3D.h"

void	perr(const char *s)
{
	ft_printf(STDERR, "%s%s%s\n", RED, s, RCOLOR);
}

void	merr(const char *s)
{
	ft_printf(STDERR, "%sMap: %s%s%s%s\n", RED, RCOLOR, LIL_RED, s, RCOLOR);
}