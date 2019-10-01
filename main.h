/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:10:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/01 20:17:19 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include "libft/inc/libft.h"

typedef struct	s_player
{
	char		letter;
	int			num;
}				t_player;
typedef struct	s_players
{
	t_player	*me;
	t_player	*opponent;
}				t_players;
#endif
