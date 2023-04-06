/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:57:39 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/02 16:57:39 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numwords(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			num++;
			continue ;
		}
		s++;
	}
	return (num);
}

static char	*appendword(char **arr, const char **s, char c)
{
	char	*sub;

	sub = ft_substr(*s, 0, ft_strchr(*s, c) - *s);
	*arr = sub;
	*s = ft_strchr(*s, c);
	return (sub);
}

static	void	*ft_clearshit(char	**start)
{
	unsigned int	i;

	i = 0;
	while (start[i])
		free(start[i++]);
	free(start);
	return (NULL);
}

char	**ft_allocate(unsigned int num, char ***start, char ***end)
{
	*start = malloc(num * sizeof(char *));
	*end = *start;
	return (*start);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr[2];

	if (!ft_allocate(numwords(s, c) + 1, &ptr[1], &ptr[0]))
		return (NULL);
	while (*s)
	{
		while (*s && (*s != c))
		{
			if (ft_strchr(s, c))
			{
				if (!appendword(ptr[0], &s, c))
					return (ft_clearshit(ptr[1]));
				ptr[0]++;
				continue ;
			}
			if (!appendword(ptr[0], &s, '\0'))
				return (ft_clearshit(ptr[1]));
			ptr[0]++;
		}
		if (*s)
			s++;
	}
	*ptr[0] = NULL;
	return (ptr[1]);
}
