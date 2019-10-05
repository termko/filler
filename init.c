/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 20:42:26 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:09:47 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		cycle(t_game *game)
{
	while (1)
	{
		if (init_field(game))
			return (1);
		if (init_heatmap(game))
			return (1);
		if (init_piece(game))
			return (1);
		if (try_heatmap(game))
			return (1);
		if (best_choice(game))
			return (1);
		free_all(game);
	}
	return (0);
}

int		init(void)
{
	t_game	*game;
	char	*str;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (1);
	if (!(str = ft_strnew(1024)))
		return (1);
	game->places = NULL;
	game->players.me.letter = '\0';
	game->players.me.num = 0;
	game->players.opponent.letter = '\0';
	game->players.opponent.num = 0;
	game->field.map = NULL;
	game->field.heatmap = NULL;
	game->field.piece = NULL;
	game->field.map_size.x = 0;
	game->field.map_size.y = 0;
	game->field.piece_size.x = 0;
	game->field.piece_size.y = 0;
	if (read_str(str))
		return (1);
	if (init_player(game, str))
		return (1);
	free(str);
	return (cycle(game));
}
