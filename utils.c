/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:36:54 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/05 18:04:22 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	append_str(char *str, char *buff)
{
	int		i;

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

void	put_v2(t_v2 best)
{
	ft_putnbr(best.x);
	ft_putchar(' ');
	ft_putnbr(best.y);
	ft_putchar('\n');
}

int		calc_from_center(t_game *game, int i, int j)
{
	int		ret;

	ret = ft_abs(i - game->field.map_size.x / 2) +
		ft_abs(j - game->field.map_size.y / 2);
	return (ret);
}
