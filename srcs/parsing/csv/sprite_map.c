/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:17:51 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/25 08:21:38 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

// void	print_sprite_map(t_sprite_map *map)
// {
// 	t_sprite_map	*s;

// 	for (s = map; s != NULL; s = s->hh.next)
// 	{
// 		printf("Key: %s, Value: %d\n", s->key, s->value);
// 	}
// }

void	init_sprite_map(t_vars *v, t_sprite_map **map)
{
	int				i;
	t_sprite_entry	*entry;
	t_sprite_map	*s;

	entry = create_entries();
	*map = NULL;
	i = -1;
	while (entry[++i].name != NULL)
	{
		s = malloc(sizeof(t_sprite_map));
		if (!s)
			(merr("Malloc Failed"), clean_exit((char **)v->img, INT_MAX, v, 0));
		s->key = entry[i].name;
		s->value = entry[i].id;
		HASH_ADD_KEYPTR(hh, *map, s->key, len(s->key), s);
	}
}

int	get_sprite_id(t_sprite_map *map, const char *key)
{
	t_sprite_map	*s;

	HASH_FIND_STR(map, key, s);
	if (!s)
		return (EPARMOR);
	return (s->value);
}
