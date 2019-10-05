/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heatmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:21:33 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 21:12:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		lesser_check(int lesser, int heat)
{
	if ((!lesser || lesser > heat) && heat > 0)
		return (heat);
	return (lesser);
}

int		lesser_surround(t_game *game, int **heat, int i, int j)
{
	int		less;
	int		len;
	int		wid;

	len = game->field.map_size.y;
	wid = game->field.map_size.x;
	less = 0;
	if (i - 1 >= 0)
	{
		less = (j - 1 >= 0 ? lesser_check(less, heat[i - 1][j - 1]) : less);
		less = lesser_check(less, heat[i - 1][j]);
		less = (j + 1 < len ? lesser_check(less, heat[i - 1][j + 1]) : less);
	}
	less = (j - 1 >= 0 ? lesser_check(less, heat[i][j - 1]) : less);
	less = (j + 1 < len ? lesser_check(less, heat[i][j + 1]) : less);
	if (i + 1 < len)
	{
		less = (j - 1 >= 0 ? lesser_check(less, heat[i + 1][j - 1]) : less);
		less = lesser_check(less, heat[i + 1][j]);
		less = (j + 1 < len ? lesser_check(less, heat[i + 1][j + 1]) : less);
	}
	if (!((less < heat[i][j] - 1 || !heat[i][j]) && less > 0))
		return (0);
	heat[i][j] = less + 1;
	return (1);
}

int		fill_heatmap(t_game *game, int **heat)
{
	int		modified;
	int		i;
	int		j;

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
				modified = lesser_surround(game, heat, i, j);
				j++;
			}
			i++;
		}
	}
	return (0);
}
