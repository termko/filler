/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 20:36:28 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 20:56:20 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	reset_fields(t_game *game)
{
	int	i;

	if (!game->field.map || !game->field.heatmap)
		return ;
	i = 0;
	while (i < game->field.map_size.x)
	{
		free(game->field.map[i]);
		free(game->field.heatmap[i]);
		game->field.map[i] = NULL;
		game->field.heatmap[i] = NULL;
		i++;
	}
	free(game->field.map);
	free(game->field.heatmap);
	game->field.map = NULL;
	game->field.heatmap = NULL;
	game->field.map_size.x = 0;
	game->field.map_size.y = 0;
}

void	reset_pieces(t_game *game)
{
	int	i;

	if (!game->field.piece)
		return ;
	i = 0;
	while (game->field.piece[i])
	{
		free(game->field.piece[i]);
		game->field.piece[i] = NULL;
		i++;
	}
	free(game->field.piece);
	game->field.piece = NULL;
	game->field.piece_size.x = 0;
	game->field.piece_size.y = 0;
}

void	reset_places(t_game *game)
{
	t_point *tmp;

	while (game->places)
	{
		if (game->places->next)
			tmp = game->places->next;
		else
			tmp = NULL;
		free(game->places);
		game->places = tmp;
	}
}

void	free_all(t_game *game)
{
	reset_places(game);
	reset_pieces(game);
	reset_fields(game);
}
