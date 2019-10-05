/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:40:03 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:15:49 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		piece_string(t_game *game)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (i < game->field.piece_size.x)
	{
		if (!(buff = ft_strnew(game->field.piece_size.y + 1)))
			return (-1);
		if (read_str(buff))
			return (-1);
		if (!(game->field.piece[i] = ft_strnew(game->field.piece_size.y)))
			return (-1);
		j = 0;
		while (j < game->field.piece_size.y)
		{
			game->field.piece[i][j] = buff[j];
			j++;
		}
		free(buff);
		i++;
	}
	game->field.piece[i] = NULL;
	return (0);
}

int		init_piece(t_game *game)
{
	char	**split;
	char	*str;

	if (!(str = ft_strnew(1024)))
		return (-1);
	if (read_str(str))
		return (-1);
	if (!(split = ft_strsplit(str, ' ')))
		return (-1);
	if (split_check(split, 3))
		return (-1);
	game->field.piece_size.x = ft_atoi(split[1]);
	game->field.piece_size.y = ft_atoi(split[2]);
	if (!(game->field.piece = (char**)malloc(sizeof(char*) *
					(game->field.piece_size.x + 1))))
		return (-1);
	if (piece_string(game))
		return (-1);
	split_free(&split);
	return (0);
}
