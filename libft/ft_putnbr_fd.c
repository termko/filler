/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:58:08 by vellery-          #+#    #+#             */
/*   Updated: 2019/10/04 04:19:51 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_fd(int n, int fd)
{
	int copy;
	int i;

	if (n == -2147483648)
	{
		if (ft_putstr_fd("-2147483648", fd))
			return (-1);
		return (0);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	copy = n;
	i = 1;
	while (copy / 10 > 0)
	{
		i = i * 10;
		copy = copy / 10;
	}
	while (i > 0)
	{
		if (ft_putchar_fd(n / i % 10 + '0', fd))
			return (-1);
		i = i / 10;
	}
	return (0);
}
