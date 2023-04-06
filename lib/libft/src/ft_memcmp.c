/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:44:22 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/16 21:15:23 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;

	if (!s1 || !s2)
		return (0);
	while (n--)
	{
		uc1 = *(unsigned char *)s1;
		uc2 = *(unsigned char *)s2;
		if (uc1 != uc2)
			return (uc1 - uc2);
		s1++;
		s2++;
	}
	return (0);
}
