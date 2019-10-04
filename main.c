/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:45:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/04 07:03:06 by ydavis           ###   ########.fr       */
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

int		read_str(char *str)
{
	char	buff[1];

	while (1)
	{
		read(0, buff, 1);
		if (buff[0] == '\0')
			return (-1);
		append_str(str, buff);
		if (buff[0] == '\n')
			return (0);
	}
}

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

int		init_player(t_game *game, char *str)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		return (-1);
	if (!split[0] || !split[1] || !split[2] || !split[3] || !split[4])
		return (-1);
	if (check_player(split))
		return (-1);
	game->players.me.num = (split[2][1] == '1' ? 1 : 2);
	game->players.opponent.num = (split[2][1] == '1' ? 2 : 1);
	game->players.me.letter = (split[2][1] == '1' ? 'O' : 'X');
	game->players.opponent.letter = (split[2][1] == '1' ? 'X' : 'O');
	return (0);
}

int		lesser_surround(t_game *game, int **heat, int i, int j)
{
	int lesser;
	int len;
	int wid;

	len = game->field.map_size.y;
	wid = game->field.map_size.x;
	lesser = 0;
	if (i - 1 >= 0)
	{
		if (j - 1 >= 0 && (!lesser || lesser > heat[i - 1][j - 1]) && heat[i - 1][j - 1] > 0)
			lesser = heat[i - 1][j - 1];
		if ((!lesser || lesser > heat[i - 1][j]) && heat[i - 1][j] > 0)
			lesser = heat[i - 1][j];
		if (j + 1 < len && (!lesser || lesser > heat[i - 1][j + 1]) && heat[i - 1][j + 1] > 0)
			lesser = heat[i - 1][j + 1];
	}
	if (j - 1 >= 0 && (!lesser || lesser > heat[i][j - 1]) && heat[i][j - 1] > 0)
		lesser = heat[i][j - 1];
	if (j + 1 < len && (!lesser || lesser > heat[i][j + 1]) && heat[i][j + 1] > 0)
		lesser = heat[i][j + 1];
	if (i + 1 < wid)
	{	
		if (j - 1 >= 0 && (!lesser || lesser > heat[i + 1][j - 1]) && heat[i + 1][j - 1] > 0)
			lesser = heat[i + 1][j - 1];
		if ((!lesser || lesser > heat[i + 1][j]) && heat[i + 1][j] > 0)
			lesser = heat[i + 1][j];
		if (j + 1 < len && (!lesser || lesser > heat[i + 1][j + 1]) && heat[i + 1][j + 1] > 0)
			lesser = heat[i + 1][j + 1];
	}
	return (lesser);
}

int		fill_heatmap(t_game *game, int **heat)
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
				if ((value < heat[i][j] - 1 && value > 0) || !heat[i][j])
				{
					heat[i][j] = value + 1;
					modified = 1;
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

int		initial_heat(t_game *game, int **heat)
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
			if (ft_toupper(game->field.map[i][j]) == me)
				heat[i][j] = -2;
			else if (ft_toupper(game->field.map[i][j]) == enemy)
				heat[i][j] = -1;
			else
				heat[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int		around_enemy(t_game *game, int **heat, int i, int j)
{
	int len;
	int wid;

	len = game->field.map_size.y;
	wid = game->field.map_size.x;
	if (i - 1 >= 0)
	{
		if (j - 1 >= 0 && heat[i - 1][j - 1] == -1)
			return (1);
		if (heat[i - 1][j] == -1)
			return (1);
		if (j + 1 < len && heat[i - 1][j + 1] == -1)
			return (1);
	}
	if (j - 1 >= 0 && heat[i][j - 1] == -1)
		return (1);
	if (j + 1 < len && heat[i][j + 1] == -1)
		return (1);
	if (i + 1 < wid)
	{	
		if (j - 1 >= 0 && heat[i + 1][j - 1] == -1)
			return (1);
		if (heat[i + 1][j] == -1)
			return (1);
		if (j + 1 < len && heat[i + 1][j + 1] == -1)
			return (1);
	}
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

	check_malloc(heat = (int**)malloc(sizeof(int*) * (game->field.map_size.x)));
	i = 0;
	while (i < game->field.map_size.x)
	{
		check_malloc(heat[i] = (int*)malloc(sizeof(int) * (game->field.map_size.y)));
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

int		fill_field(t_game *game)
{
	int		i;
	int		j;
	int		flag;
	char	*buff;

	check_malloc(game->field.map = (char**)malloc(sizeof(char*) * (game->field.map_size.x + 1)));
	game->field.map[game->field.map_size.x] = NULL;
	i = 0;
	flag = 0;
	while (i < game->field.map_size.x)
	{
		check_malloc(buff = ft_strnew(game->field.map_size.y + 6));
		if (read_str(buff))
			return (-1);
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
		free(buff);
		flag = 1;
	}
	game->field.map[i] = NULL;
	return (0);
}

int		init_field(t_game *game)
{
	char	**split;
	char	*tmp;

	check_malloc(tmp = ft_strnew(1024));
	if (read_str(tmp))
		return (-1);
	check_malloc(split = ft_strsplit(tmp, ' '));
	if (!split[0])
		return (-1);
	if (!split[1])
	   return (-1);
	if (!split[2])
		return (-1);
	if (ft_strcmp(split[0], "Plateau") || ft_atoi(split[1]) <= 0 || ft_atoi(split[2]) <= 0)
		return (-1);
	game->field.map_size.x = ft_atoi(split[1]);
	game->field.map_size.y = ft_atoi(split[2]);
	split_free(&split);
	free(tmp);
	if (fill_field(game))
		return (-1);
	return (0);
}

void		fprintf_arr(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			fprintf(stderr, "%d ", game->field.heatmap[i][j]);
			j++;
		}
		fprintf(stderr, "\n");
		i++;
	}
}

void	put_v2(t_v2 best)
{
	ft_putnbr(best.x);
	ft_putchar(' ');
	ft_putnbr(best.y);
	ft_putchar('\n');
}

int		best_choice(t_game *game)
{
	t_v2	best;
	int		sum;
	t_point	*tmp;

	sum = -1;
	best.x = -1;
	best.y = -1;
	tmp = game->places;
	while (tmp)
	{
		if (tmp->score < sum || sum == -1)
		{
			sum = tmp->score;
			best = tmp->p;
		}
		tmp = tmp->next;
	}
	if (best.x == -1 || best.y == -1)
		return (-1);
	put_v2(best);
	return (0);
}

int		can_put(t_game *game, int i, int j)
{
	int		k;
	int		l;
	int		sum;
	int		flag;
	t_v2	map;

	map.x = game->field.map_size.x;
	map.y = game->field.map_size.y;
	sum = 0;
	flag = 0;
	k = 0;
	while (k < game->field.piece_size.x)
	{
		if (k + i >= map.x)
			return (-1);
		l = 0;
		while (l < game->field.piece_size.y)
		{
			if (l + j >= map.y)
				return (-1);
			if (game->field.piece[k][l] == '*')
			{
//				fprintf(stderr, "%d %d %d %d\n", i, j, k, l);
				if (ft_toupper(game->field.map[k + i][l + j]) == game->players.opponent.letter)
					return (-1);
				if (ft_toupper(game->field.map[k + i][l + j]) == game->players.me.letter)
				{
					if (flag)
						return (-1);
					flag = 1;
				}
				else
				{
					sum += game->field.heatmap[k + i][l + j];
				}
			}
			l++;
		}
		k++;
	}
	if (!flag)
		return (-1);
	return (sum);
}

void	put_piece(t_game *game, int sum, int i, int j)
{
	t_point *tmp;

	if (!game->places)
	{
		check_malloc(game->places = (t_point*)malloc(sizeof(t_point)));
		tmp = game->places;
	}
	else
	{
		tmp = game->places;
		while (tmp->next)
			tmp = tmp->next;
		check_malloc(tmp->next = (t_point*)malloc(sizeof(t_point)));
		tmp = tmp->next;
	}
	tmp->p.x = i;
	tmp->p.y = j;
	tmp->score = sum;
	tmp->next = NULL;
}

int		try_heatmap(t_game *game)
{
	int	i;
	int	j;
	int	sum;

	i = 0;
	while (i < game->field.map_size.x)
	{
		j = 0;
		while (j < game->field.map_size.y)
		{
			if ((sum = can_put(game, i, j)) >= 0)
				put_piece(game, sum, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int		init_piece(t_game *game)
{
	int		i;
	int		j;
	char	**split;
	char	*buff;
	char	*str;

	check_malloc(str = ft_strnew(1024));
	if (read_str(str))
		return (-1);
	check_malloc(split = ft_strsplit(str, ' '));
	game->field.piece_size.x = ft_atoi(split[1]);
	game->field.piece_size.y = ft_atoi(split[2]);
	check_malloc(game->field.piece = (char**)malloc(sizeof(char*) * (game->field.piece_size.x + 1)));
	i = 0;
	while (i < game->field.piece_size.x)
	{
		check_malloc(buff = ft_strnew(game->field.piece_size.y + 1));
		if (read_str(buff))
			return (-1);
		check_malloc(game->field.piece[i] = ft_strnew(game->field.piece_size.y));
		j = 0;
		while (j < game->field.piece_size.y)
		{
			game->field.piece[i][j] = buff[j];
			j++;
		}
		i++;
		free(buff);
	}
	game->field.piece[i] = NULL;
	split_free(&split);
	return (0);
}

void	reset_fields(t_game *game)
{
	int i;

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
	int i;

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
	t_point	*tmp;

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

int		main(void)
{
	char		*str;
	t_game		*game;

	check_malloc(game = (t_game*)malloc(sizeof(t_game)));
	check_malloc(str = ft_strnew(1024));
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
	free(str);
	return (0);
}
