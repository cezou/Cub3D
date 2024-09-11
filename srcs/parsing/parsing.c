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

bool	is_everything_set(t_is_set set)
{
	return (set.c && set.f && set.ea && set.no && set.so && set.we);
}

t_is_set	init_is_set(void)
{
	t_is_set	is_set;

	is_set.c = 0;
	is_set.f = 0;
	is_set.ea = 0;
	is_set.no = 0;
	is_set.so = 0;
	is_set.we = 0;
	return (is_set);
}

void	clean_exit(char **l, int fd)
{
	close(fd);
	freeall(l);
	exit(FAIL);
}

bool	is_texture(char *s)
{
	return (!cmp(s, "NO") || !cmp(s, "SO") || !cmp(s, "WE") || !cmp(s, "EA"));
}

bool	is_color(char *s)
{
	return (!cmp(s, "F") || !cmp(s, "C"));
}

int	set_texture(t_infos *i, char **l, int ind)
{
	if (!cmp(l[0], "NO"))
	{
		if (i->is_set.no)
			return (lerr(ind, "duplicate ID"), -1);
		// if ()
		// i->is_set.no = 1;
	}
	return (0);
}

int	set_color(t_infos *i, char **l, int ind)
{
	(void)i;
	(void)l;
	(void)ind;
	return (0);
}

int	set_a_value(t_infos *i, char **l, int ind)
{
	if (is_texture(l[0]))
		return (set_texture(i, l, ind));
	if (is_color(l[0]))
		return (set_color(i, l, ind));
	return (lerr(ind, "Unvalid ID"), -1);
}

void	parse_file(int fd, t_infos *info)
{
	size_t	i;
	char	*line;
	char	**l;

	info->is_set = init_is_set();
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		l = ft_split(line, WHITESPACES);
		free(line);
		if ((!l || !l[0]) && (freeall(l), i++))
			continue ;
		if (tab_len(l) != 2)
			(lerr(i + 1, "Invalid line: too much values as all IDs arent set"),
				clean_exit(l, fd));
		if (set_a_value(info, l, i) == -1)
			clean_exit(l, fd);
		freeall(l);
		if (is_everything_set(info->is_set))
			break ;
		i++;
	}
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
	parse_file(fd, i);
	close(fd);
}