#include "../../includes/cub3D.h"

static bool	isnt_cub_ended(const char *s)
{
	int	i;

	if (ft_strlen(s) < 4)
		return (1);
	i = ft_strlen(s) - 1;
	if (s[i] == 'b' && s[i - 1] == 'u' && s[i - 2] == 'c' && s[i - 3] == '.')
		return (0);
	return (1);
}

void	parsing(char *file, t_infos *i)
{
	int fd;

	(void)i;
	if (isnt_cub_ended(file))
		(merr("file name needs to end with \".cub\""), exit(FAIL));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(merr("file doesn't exist or open failed"), exit(FAIL));
	close(fd);
	// if (open(file_path, ))
}