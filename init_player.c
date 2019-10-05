/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:04:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 18:53:30 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_player(char **split)
{
	if (ft_strcmp(split[0], "$$$"))
		return (-1);
	if (ft_strcmp(split[1], "exec"))
		return (-1);
	if (ft_strcmp(split[2], "p1") && ft_strcmp(split[2], "p2"))
		return (-1);
	if (ft_strcmp(split[3], ":"))
		return (-1);
	if (ft_strcmp(split[4], "[./ydavis.filler]\n"))
		return (-1);
	return (0);
}

int		split_check(char **split, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (!split[i])
			return (-1);
		i++;
	}
	if (split[i])
		return (-1);
	return (0);
}

int		init_player(t_game *game, char *str)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		return (-1);
	if (split_check(split, 5))
		return (-1);
	if (check_player(split))
		return (-1);
	game->players.me.num = (split[2][1] == '1' ? 1 : 2);
	game->players.me.letter = (game->players.me.num == 1 ? 'O' : 'X');
	game->players.opponent.num = (split[2][1] == '1' ? 2 : 1);
	game->players.opponent.letter = (game->players.me.num == 1 ? 'X' : 'O');
	return (0);
}
