/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:30:03 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 19:39:16 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		field_string(t_game *game, int i)
{
	int		j;
	char	*buff;

	if (!(buff = ft_strnew(game->field.map_size.y + 6)))
		return (-1);
	if (read_str(buff))
		return (-1);
	if (i >= 0)
	{
		if (!(game->field.map[i] = ft_strnew(game->field.map_size.y)))
			return (-1);
		j = 4;
		while (j < game->field.map_size.y + 4)
		{
			game->field.map[i][j - 4] = buff[j];
			j++;
		}
	}
	free(buff);
	return (0);
}

int		fill_field(t_game *game)
{
	int		i;

	if (!(game->field.map = (char**)malloc(sizeof(char*) *
					(game->field.map_size.x + 1))))
		return (-1);
	game->field.map[game->field.map_size.x] = NULL;
	i = -1;
	while (i < game->field.map_size.x)
	{
		if (field_string(game, i))
			return (-1);
		i++;
	}
	game->field.map[i] = NULL;
	return (0);
}

int		init_field(t_game *game)
{
	char	**split;
	char	*tmp;

	if (!(tmp = ft_strnew(1024)))
		return (-1);
	if (read_str(tmp))
		return (-1);
	if (!(split = ft_strsplit(tmp, ' ')))
		return (-1);
	if (split_check(split, 3))
		return (-1);
	if (ft_strcmp(split[0], "Plateau"))
		return (-1);
	game->field.map_size.x = ft_atoi(split[1]);
	game->field.map_size.y = ft_atoi(split[2]);
	split_free(&split);
	free(tmp);
	if (fill_field(game))
		return (-1);
	return (0);
}
