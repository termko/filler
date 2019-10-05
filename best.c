/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 20:48:06 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:18:01 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_best(t_point *tmp, int *sum, int *from_center, t_v2 *best)
{
	if (tmp->score < *sum || *sum == -1)
	{
		*sum = tmp->score;
		*from_center = tmp->from_center;
		best->x = tmp->p.x;
		best->y = tmp->p.y;
	}
	else if (tmp->score == *sum && (tmp->from_center < *from_center ||
				*from_center < -1))
	{
		*sum = tmp->score;
		*from_center = tmp->from_center;
		best->x = tmp->p.x;
		best->y = tmp->p.y;
	}
}

int		best_choice(t_game *game)
{
	t_v2	best;
	int		sum;
	int		from_center;
	t_point	*tmp;
	int		i;

	sum = -1;
	from_center = -1;
	best.x = -1;
	best.y = -1;
	i = 0;
	tmp = game->places;
	while (tmp)
	{
		set_best(tmp, &sum, &from_center, &best);
		tmp = tmp->next;
		i++;
	}
	if (best.x == -1 || best.y == -1)
		return (-1);
	put_v2(best);
	return (0);
}
