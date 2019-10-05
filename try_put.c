/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:48:44 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:09:32 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_put(t_game *game, t_v2 m, t_v2 p, t_v2 *flsum)
{
	while (p.y < game->field.piece_size.y)
	{
		if (p.y + m.y > game->field.map_size.y)
			return (-1);
		if (game->field.piece[p.x][p.y] == '*')
		{
			if (ft_toupper(game->field.map[p.x + m.x][p.y + m.y]) ==
					game->players.opponent.letter)
				return (-1);
			if (ft_toupper(game->field.map[p.x + m.x][p.y + m.y]) ==
					game->players.me.letter)
			{
				if (flsum->y)
					return (-1);
				flsum->y = 1;
			}
			else
				flsum->x += game->field.heatmap[p.x + m.x][p.y + m.y];
		}
		p.y++;
	}
	return (0);
}

int		can_put(t_game *game, int i, int j)
{
	t_v2	piece;
	t_v2	map;
	t_v2	flsum;

	flsum.x = 0;
	flsum.y = 0;
	map.x = i;
	map.y = j;
	piece.x = 0;
	while (piece.x < game->field.piece_size.x)
	{
		if (piece.x + map.x >= game->field.map_size.x)
			return (-1);
		piece.y = 0;
		if (check_put(game, map, piece, &flsum))
			return (-1);
		if (flsum.y > 1)
			return (-1);
		piece.x++;
	}
	if (!flsum.y)
		return (-1);
	return (flsum.x);
}

int		put_piece(t_game *game, int sum, int i, int j)
{
	t_point	*tmp;

	if (!game->places)
	{
		if (!(game->places = (t_point*)malloc(sizeof(t_point))))
			return (-1);
		tmp = game->places;
	}
	else
	{
		tmp = game->places;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_point*)malloc(sizeof(t_point))))
			return (-1);
		tmp = tmp->next;
	}
	tmp->p.x = i;
	tmp->p.y = j;
	tmp->score = sum;
	tmp->from_center = calc_from_center(game, i, j);
	tmp->next = NULL;
	return (0);
}

int		try_heatmap(t_game *game)
{
	int		i;
	int		j;
	int		sum;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			if ((sum = can_put(game, i, j)) >= 0)
				if (put_piece(game, sum, i, j))
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
