/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:24:30 by vellery-          #+#    #+#             */
/*   Updated: 2019/10/04 04:20:29 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putstr_fd(char const *s, int fd)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) < 0)
			return (-1);
		i++;
	}
	return (0);
}
