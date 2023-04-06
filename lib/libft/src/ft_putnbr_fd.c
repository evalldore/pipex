/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:31:55 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/27 23:56:54 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	unsigned int	cur;
	char			c;
	int				i;

	i = 1;
	cur = (unsigned int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		cur *= -1;
		i++;
	}
	c = (cur % 10) + '0';
	if (cur >= 10)
		i += ft_putnbr_fd((cur / 10), fd);
	write(fd, &c, 1);
	return (i);
}
