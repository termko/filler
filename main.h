/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:10:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/01 23:13:00 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include "libft/inc/libft.h"
# include <stdlib.h>
# include <unistd.h>

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
typedef struct	s_game
{
	t_players	players;
	t_field		field;
}				t_game;
#endif
