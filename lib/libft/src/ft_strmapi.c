/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:20:31 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/20 20:34:21 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			l;
	char			*ns;

	if (!s || !f)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	ns = malloc(l + 1);
	if (!ns)
		return (NULL);
	ft_strlcpy(ns, s, l + 1);
	while (ns[i])
	{
		ns[i] = f(i, ns[i]);
		i++;
	}
	return (ns);
}
