/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:16:36 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/27 19:37:38 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

t_sprite_entry	*create_entries(void)
{
	static t_sprite_entry	entries[] = {{"EPARMOR", EPARMOR},
	{"EPARMOR1", EPARMOR1}, {"ESTIM", ESTIM}, {"EMEDI", EMEDI},
	{"EPCLIP", EPCLIP}, {"EPSHELL", EPSHELL}, {"EPROCK", EPROCK},
	{"EPCELL", EPCELL}, {"EBKEY", EBKEY}, {"EYKEY", EYKEY},
	{"ERKEY", ERKEY}, {"EBSKEY", EBSKEY}, {"EYSKEY", EYSKEY},
	{"ERSKEY", ERSKEY}, {"EPBFG", EPBFG}, {"EPSHOTGUN", EPSHOTGUN},
	{"EPGATLIN", EPGATLIN}, {"EPROCKETL", EPROCKETL},
	{"EPPLASMA", EPPLASMA}, {"EPCHAINSAW", EPCHAINSAW},
	{"EPSUPERSHOTGUN", EPSUPERSHOTGUN}, {"EHANGCORPSE01", EHANGCORPSE01},
	{"EHANGCORPSE02", EHANGCORPSE02}, {"EHANGCORPSE03", EHANGCORPSE03},
	{"EFIRELAMP01", EFIRELAMP01}, {NULL, -1}};

	return (entries);
}

void	free_sprite_map(t_sprite_map **map)
{
	t_sprite_map	*current;
	t_sprite_map	*tmp;

	if (!*map)
		return ;
	HASH_ITER(hh, *map, current, tmp)
{
	(void)tmp;
	HASH_DEL(*map, current);
	free(current);
}

}
