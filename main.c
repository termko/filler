/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:45:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/03 23:27:35 by ydavis           ###   ########.fr       */
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
		game->players.me.letter = (player == 1 ? 'O' : 'X');
	}
	else
	{
		game->players.opponent.num = player;
		game->players.opponent.letter = (player == 1 ? 'O' : 'X');
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

int		lesser_surround(t_game *game, int **heat, int i, int j)
{
	int lesser;
	int len;
	int wid;

	len = game->field.map_size.y;
	wid = game->field.map_size.x;
	lesser = INT_MAX - 1;
	if (i - 1 >= 0)
	{
		if (j - 1 >= 0 && lesser > heat[i - 1][j - 1] && heat[i - 1][j - 1] > 0)
			lesser = heat[i - 1][j - 1];
		if (lesser > heat[i - 1][j] && heat[i - 1][j] > 0)
			lesser = heat[i - 1][j];
		if (j + 1 < len && lesser > heat[i - 1][j + 1] && heat[i - 1][j + 1] > 0)
			lesser = heat[i - 1][j + 1];
	}
	if (j - 1 >= 0 && lesser > heat[i][j - 1] && heat[i][j - 1] > 0)
		lesser = heat[i][j - 1];
	if (j + 1 < len && lesser > heat[i][j + 1] && heat[i][j + 1] > 0)
		lesser = heat[i][j + 1];
	if (i + 1 < wid)
	{	
		if (j - 1 >= 0 && lesser > heat[i + 1][j - 1] && heat[i + 1][j - 1] > 0)
			lesser = heat[i + 1][j - 1];
		if (lesser > heat[i + 1][j] && heat[i + 1][j] > 0)
			lesser = heat[i + 1][j];
		if (j + 1 < len && lesser > heat[i + 1][j + 1] && heat[i + 1][j + 1] > 0)
			lesser = heat[i + 1][j + 1];
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

void	second_init_heat(t_game *game, int **heat)
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
	second_init_heat(game, heat);
	fill_heatmap(game, heat);
	game->field.heatmap = heat;
}

void	fill_field(t_game *game)
{
	int		i;
	int		j;
	int		flag;
	char	*buff;

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
		read(0, buff, 1);
		flag = 1;
	}
	game->field.map[i] = NULL;
	free(buff);
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
			printf("%d ", game->field.heatmap[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	put_v2(t_v2 best)
{
	char	*x;
	char	*y;
	char	*out;

	x = ft_itoa(best.x);
	y = ft_itoa(best.y);
	check_malloc(out = ft_strnew(ft_strlen(x) + ft_strlen(y) + 2));
	out = ft_strcat(out, x);
	out = ft_strcat(out, " ");
	out = ft_strcat(out, y);
	out = ft_strcat(out, "\n");
	ft_putstr(out);
}

void	best_choice(t_game *game)
{
	t_v2	best;
	int		sum;
	t_point	*tmp;

	sum = 0;
	best.x = 0;
	best.y = 0;
	tmp = game->places;
	while (tmp)
	{
		if (tmp->score < sum || !sum)
		{
			sum = tmp->score;
			best = tmp->p;
		}
		tmp = tmp->next;
	}
	put_v2(best);
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
		l = 0;
		while (l < game->field.piece_size.y)
		{
			if (game->field.piece[k][l] == '*')
			{
				if (ft_toupper(game->field.map[k + i][l + j]) == game->players.me.letter)
				{
					if (flag)
						return (-1);
					flag = 1;
				}
				else if (game->field.map[k + i][l + j] != '.')
					return (-1);
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

void	try_heatmap(t_game *game)
{
	int	i;
	int	j;
	int	sum;

	i = 0;
	while (i < game->field.map_size.x - game->field.piece_size.x)
	{
		j = 0;
		while (j < game->field.map_size.x - game->field.piece_size.y)
		{
			if ((sum = can_put(game, i, j)) > 0)
				put_piece(game, sum, i, j);
			j++;
		}
		i++;
	}
}

void	init_piece(t_game *game, char *str)
{
	int		i;
	int		j;
	char	**split;
	char	*buff;

	check_malloc(split = ft_strsplit(str, ' '));
	game->field.piece_size.x = ft_atoi(split[1]);
	game->field.piece_size.y = ft_atoi(split[2]);
	check_malloc(buff = ft_strnew(game->field.piece_size.y + 1));
	check_malloc(game->field.piece = (char**)malloc(sizeof(char*) * (game->field.piece_size.x + 1)));
	i = 0;
	while (i < game->field.piece_size.x)
	{
		read(0, buff, game->field.piece_size.y + 1);
		check_malloc(game->field.piece[i] = ft_strnew(game->field.piece_size.y));
		j = 0;
		while (j < game->field.piece_size.y)
		{
			game->field.piece[i][j] = buff[j];
			j++;
		}
		i++;
	}
	game->field.piece[i] = NULL;
	free(buff);
	split_free(&split);
}

void	reset_fields(t_game *game)
{
	int i;

	if (!game->field.map || !game->field.heatmap)
		return ;
	i = 0;
	while (game->field.map[i])
	{
		free(game->field.map[i]);
		free(game->field.heatmap[i]);
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

void	read_str(char *str)
{
	char	buff[1];

	while (1)
	{
		read(0, buff, 1);
		append_str(str, buff);
		if (buff[0] == '\n')
			return ;
	}
}

int		main(void)
{
	int			got;
//	char		buff[1];
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
	got = 0;
	read_str(str);
	if (!init_player(game, str))
		return (1);
	free(str);
	check_malloc(str = ft_strnew(1024));
	while (1) // REMAKE WITH HARD CODED TIMES!!!!!!!!
	{
		/*
		read_str(str);
		append_str(str, buff);
		if (buff[0] == '\n')
		{
			if (ft_strstr(str, "exec p1"))
				init_player(game, str, 1);
			else if (ft_strstr(str, "exec p2"))
				init_player(game, str, 2);
			else if (ft_strstr(str, "Plateau"))
			{
			//	reset_fields(game);
				game->field.map = NULL;
				game->field.heatmap = NULL;
				game->field.map_size.x = 0;
				game->field.map_size.y = 0;
				init_field(game, str);
				init_heatmap(game);
			}
			else if (ft_strstr(str, "Piece"))
			{
				got++;
//				printf("turn %d\n", got);
//					printf("IS THIS REAL???\n");
			//	reset_pieces(game);
			//	reset_places(game);
				game->places = NULL;
				game->field.piece = NULL;
				init_piece(game, str);
				try_heatmap(game);
					//print_arr(game);
				if (got % 2 == game->players.me.num)
				{
					best_choice(game);
				}
			}
			free(str);
			check_malloc(str = ft_strnew(1024));
		//}
		*/
	}
	free(str);
}
