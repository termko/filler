/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:45:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/01 20:44:23 by ydavis           ###   ########.fr       */
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
	t_player *now;

	if (ft_strstr(str, "ydavis.filler") && !players.me->num)
	{
		now = players.me;
	}
	else
	{
		now = players.opponent;
	}
	now->letter = 'O';
	now->num = player;
}

int		main(void)
{
	int 		i;
	char		*buff;
	char		*str;
	int			count;
	t_players	players;

	check_malloc(buff = ft_strnew(2));
	check_malloc(str = ft_strnew(1024));
	check_malloc(players.me = (t_player*)malloc(sizeof(t_player)));
	check_malloc(players.opponent = (t_player*)malloc(sizeof(t_player)));
	players.me->letter = '\0';
	players.me->num = 0;
	players.opponent->letter = '\0';
	players.opponent->num = 0;
	count = 0;
	while ((i = read(0, buff, 1)) > 0)
	{
		append_str(str, buff);
		if (buff[0] == '\n')
		{
			if (ft_strstr(str, "exec p1"))
				init_player(players, str, 1);
			if (ft_strstr(str, "exec p2"))
				init_player(players, str, 2);
		}
	}
}
