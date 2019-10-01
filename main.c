/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:45:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/01 23:22:24 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_malloc(void *addr)
{
	if (!addr)
		exit(1);
}

void	append_str(char *str, char *buff)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	str[i] = buff[0];
}

void	init_player(t_players players, char *str, int player)
{
	t_player now;

	if (ft_strstr(str, "ydavis.filler") && !players.me.num)
	{
		now = players.me;
	}
	else
	{
		now = players.opponent;
	}
	now.letter = 'O';
	now.num = player;
}

void	split_free(char ***split)
{
	char	**tmp;
	int		i;

	tmp = *split;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	fill_field(t_game game)
{
	int		i;
	int		j;
	char	*buff;

	check_malloc(buff = ft_strnew(1));
	check_malloc(game.field.map = (char**)malloc(sizeof(char*) * (game.field.map_size.x + 1)));
	game.field.map[game.field.map_size.x] = NULL;
	i = 0;
	while (i < game.field.map_size.x)
	{
		check_malloc(game.field.map[i] = (char*)malloc(sizeof(char) * (game.field.map_size.y + 1)));
		game.field.map[i][game.field.map_size.y] = '\0';
		j = 0;
		while (j < game.field.map_size.y)
		{
			read(0, &(game.field.map[i][j]), 1); // DEFEND
			j++;
		}
		read(0, buff, 1);
		i++;
		printf("[%d] %s\n", i,  game.field.map[i]);
	}
}

void	init_field(t_game game, char *str)
{
	char	**tmp;

	check_malloc(tmp = ft_strsplit(str, ' '));
	game.field.map_size.x = ft_atoi(tmp[1]);
	game.field.map_size.y = ft_atoi(tmp[2]);
	split_free(&tmp);
	fill_field(game);
}

int		main(void)
{
	int 		i;
	char		*buff;
	char		*str;
	int			count;
	t_game		game;

	check_malloc(buff = ft_strnew(2));
	check_malloc(str = ft_strnew(1024));
	game.players.me.letter = '\0';
	game.players.me.num = 0;
	game.players.opponent.letter = '\0';
	game.players.opponent.num = 0;
	count = 0;
	while ((i = read(0, buff, 1)) > 0)
	{
		append_str(str, buff);
		if (buff[0] == '\n')
		{
			printf("%s\n", str);
			if (ft_strstr(str, "exec p1"))
				init_player(game.players, str, 1);
			else if (ft_strstr(str, "exec p2"))
				init_player(game.players, str, 2);
			else if (ft_strstr(str, "Plateau"))
				init_field(game, str);
			free(str);
			check_malloc(str = ft_strnew(1024));
		}
	}
}
