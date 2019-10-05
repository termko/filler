/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heatmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:19:45 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 19:27:55 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		initial_heat(t_game *game, int **heat)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			heat[i][j] = 0;
			if (ft_toupper(game->field.map[i][j]) == game->players.me.letter)
				heat[i][j] = -2;
			else if (ft_toupper(game->field.map[i][j]) ==
					game->players.opponent.letter)
				heat[i][j] = -1;
			j++;
		}
		i++;
	}
	return (0);
}

int		check_enemy(t_game *game, int **heat, int i, int j)
{
	if (j - 1 >= 0 && heat[i][j - 1] == -1)
		return (1);
	if (heat[i][j - 1] == -1)
		return (1);
	if (j + 1 < game->field.map_size.y && heat[i][j + 1] == -1)
		return (1);
	return (0);
}

int		around_enemy(t_game *game, int **heat, int i, int j)
{
	if (i - 1 >= 0)
		if (check_enemy(game, heat, i - 1, j))
			return (1);
	if (check_enemy(game, heat, i, j))
		return (1);
	if (i + 1 < game->field.map_size.x)
		if (check_enemy(game, heat, i + 1, j))
			return (1);
	return (0);
}

int		second_init_heat(t_game *game, int **heat)
{
	int i;
	int j;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			if (heat[i][j] >= 0 && around_enemy(game, heat, i, j))
				heat[i][j] = 1;
			j++;
		}
		i++;
	}
	return (0);
}

int		init_heatmap(t_game *game)
{
	int		**heat;
	int		i;

	if (!(heat = (int**)malloc(sizeof(int*) * (game->field.map_size.x))))
		return (-1);
	i = 0;
	while (i < game->field.map_size.x)
	{
		if (!(heat[i] = (int*)malloc(sizeof(int) * (game->field.map_size.y))))
			return (-1);
		i++;
	}
	if (initial_heat(game, heat))
		return (-1);
	if (second_init_heat(game, heat))
		return (-1);
	if (fill_heatmap(game, heat))
		return (-1);
	game->field.heatmap = heat;
	return (0);
}
