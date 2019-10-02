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

void	init_player(t_game *game, char *str, int player)
{
	if (ft_strstr(str, "ydavis.filler") && !game->players.me.num)
	{
		game->players.me.num = player;
		game->players.opponent.num = (player == 1 ? 2 : 1);
		game->players.me.letter = (player == 1 ? 'O' : 'X');
		game->players.opponent.letter = (player == 1 ? 'X' : 'Y');
	}
	else
	{
		game->players.opponent.num = player;
		game->players.me.num = (player == 1 ? 2 : 1);
		game->players.opponent.letter = (player == 1 ? 'O' : 'X');
		game->players.me.letter = (player == 1 ? 'X' : 'Y');
	}
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

# include <limits.h>

int		lesser_surround(t_game *game, int **heat, int i, int j)
{
	int lesser;
	int len;
	int wid;

	len = game->field.map_size.y;
	wid = game->field.map_size.x;
	lesser = UINT_MAX - 1;
	if (i - 1 >= 0)
	{
		if (j - 1 >= 0)
			lesser = (lesser < heat[i - 1][j - 1] ? lesser : heat[i - 1][j - 1]);
		lesser = (lesser < heat[i - 1][j] ? lesser : heat[i - 1][j]);
		if (j + 1 < len)
			lesser = (lesser < heat[i - 1][j + 1] ? lesser : heat[i - 1][j + 1]);
	}
	if (j - 1 >= 0)
		lesser = (lesser < heat[i][j - 1] ? lesser : heat[i][j - 1]);
	if (j + 1 < len)
		lesser = (lesser < heat[i][j + 1] ? lesser : heat[i][j + 1]);
	if (i + 1 < wid)
	{	
		if (j - 1 >= 0)
			lesser = (lesser < heat[i + 1][j - 1] ? lesser : heat[i + 1][j - 1]);
		lesser = (lesser < heat[i + 1][j] ? lesser : heat[i + 1][j]);
		if (j + 1 < len)
			lesser = (lesser < heat[i + 1][j + 1] ? lesser : heat[i + 1][j + 1]);
	}
	return (lesser);
}

void	fill_heatmap(t_game *game, int **heat)
{
	int		modified;
	int		i;
	int		j;
	int		value;

	modified = 1;
	while (modified)
	{
		modified = 0;
		i = 0;
		while (i < game->field.map_size.x)
		{
			j = 0;
			while (j < game->field.map_size.y)
			{
				value = lesser_surround(game, heat, i, j);
				if (value < heat[i][j] - 1 && value >= 0)
				{
					heat[i][j] = value + 1;
					modified = 1;
				}
				j++;
			}
			i++;
		}
	}
}

void	initial_heat(t_game *game, int **heat)
{
	int		i;
	int		j;
	char	me;
	char	enemy;

	me = game->players.me.letter;
	enemy = game->players.opponent.letter;
	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			if (game->field.map[i][j] == me)
				heat[i][j] = -1;
			else if (game->field.map[i][j] == enemy)
				heat[i][j] = 0;
			else
				heat[i][j] = UINT_MAX - 1;
			j++;
		}
		i++;
	}
}

void	init_heatmap(t_game *game)
{
	int		**heat;
	int		i;

	check_malloc(heat = (int**)malloc(sizeof(int*) * (game->field.map_size.x)));
	i = 0;
	while (i < game->field.map_size.x)
	{
		check_malloc(heat[i] = (int*)malloc(sizeof(int) * (game->field.map_size.y)));
		i++;
	}
	initial_heat(game, heat);
	fill_heatmap(game, heat);
	game->field.heatmap = heat;
}

void	fill_field(t_game *game)
{
	int		i;
	int		j;
	int		flag;
	char	*buff;
	char	junk[1];

	check_malloc(buff = ft_strnew(game->field.map_size.y + 4));
	check_malloc(game->field.map = (char**)malloc(sizeof(char*) * (game->field.map_size.x + 1)));
	game->field.map[game->field.map_size.x] = NULL;
	i = 0;
	flag = 0;
	while (i < game->field.map_size.x)
	{
		read(0, buff, game->field.map_size.y + 4); // DEFEND
		if (flag)
		{
			check_malloc(game->field.map[i] = ft_strnew(game->field.map_size.y));
			j = 4;
			while (j < game->field.map_size.y + 4)
			{
				game->field.map[i][j - 4] = buff[j];
				j++;
			}
			i++;
		}
		read(0, junk, 1);
		flag = 1;
	}
}

void	init_field(t_game *game, char *str)
{
	char	**tmp;

	check_malloc(tmp = ft_strsplit(str, ' '));
	game->field.map_size.x = ft_atoi(tmp[1]);
	game->field.map_size.y = ft_atoi(tmp[2]);
	split_free(&tmp);
	fill_field(game);
}

void		print_arr(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			printf("%d", game->field.heatmap[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int		main(void)
{
	int 		i;
	char		*buff;
	char		*str;
	t_game		*game;

	check_malloc(game = (t_game*)malloc(sizeof(t_game)));
	check_malloc(buff = ft_strnew(2));
	check_malloc(str = ft_strnew(1024));
	game->players.me.letter = '\0';
	game->players.me.num = 0;
	game->players.opponent.letter = '\0';
	game->players.opponent.num = 0;
	while ((i = read(0, buff, 1)) > 0)
	{
		append_str(str, buff);
		if (buff[0] == '\n')
		{
			if (ft_strstr(str, "exec p1"))
			{
				init_player(game, str, 1);
				printf("PLAYER INITED\n");
			}
			else if (ft_strstr(str, "exec p2"))
				init_player(game, str, 2);
			else if (ft_strstr(str, "Plateau"))
			{
				init_field(game, str);
				init_heatmap(game);
				print_arr(game);
			}
			free(str);
			check_malloc(str = ft_strnew(1024));
		}
	}
}
