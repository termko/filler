/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:10:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:18:53 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include "libft/inc/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

typedef struct	s_v2
{
	int			x;
	int			y;
}				t_v2;
typedef struct	s_player
{
	char		letter;
	int			num;
}				t_player;
typedef struct	s_players
{
	t_player	me;
	t_player	opponent;
}				t_players;
typedef struct	s_field
{
	t_v2		map_size;
	t_v2		piece_size;
	char		**map;
	int			**heatmap;
	char		**piece;
}				t_field;
typedef struct	s_point
{
	t_v2			p;
	int				score;
	int				from_center;
	struct s_point	*next;
}				t_point;
typedef struct	s_game
{
	t_players	players;
	t_field		field;
	t_point		*places;
}				t_game;
void			append_str(char *str, char *buff);
void			split_free(char ***split);
int				read_str(char *str);
void			put_v2(t_v2 best);
int				calc_from_center(t_game *game, int i, int j);
int				split_check(char **split, int num);
int				init_player(t_game *game, char *str);
int				lesser_surround(t_game *game, int **heat, int i, int j);
int				fill_heatmap(t_game *game, int **heat);
int				initial_heat(t_game *game, int **heat);
int				init_heatmap(t_game *game);
int				init_field(t_game *game);
int				init_piece(t_game *game);
int				try_heatmap(t_game *game);
void			free_all(t_game *game);
int				best_choice(t_game *game);
int				init(void);
int				cycle(t_game *game);
#endif
