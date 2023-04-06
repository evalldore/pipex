/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:21:14 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/20 20:54:29 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	to_uint(int n, int *s)
{
	if (n < 0)
	{
		*s = -1;
		return ((unsigned int)(n *= -1));
	}
	*s = 1;
	return ((unsigned int) n);
}

static char	*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		j--;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			c[12];
	unsigned int	cur;
	unsigned int	i;
	int				s;

	if (n == 0)
		return (ft_strdup("0"));
	cur = to_uint(n, &s);
	i = 0;
	while (cur > 0)
	{
		c[i++] = '0' + (cur % 10);
		cur /= 10;
	}
	if (s < 0)
		c[i++] = '-';
	c[i] = '\0';
	return (ft_strdup(ft_strrev(c)));
}
