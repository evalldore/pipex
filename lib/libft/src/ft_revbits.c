/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:11:06 by evallee-          #+#    #+#             */
/*   Updated: 2023/03/02 03:27:12 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	ft_revbits(int64_t num)
{
	unsigned int	i;
	unsigned int	nbits;
	uint64_t		revbits;

	nbits = sizeof(num) * 8;
	revbits = 0;
	i = 0;
	while (i < nbits)
	{
		if (num & (1 << i))
			revbits |= 1 << ((nbits - 1) - i);
		i++;
	}
	return (revbits);
}
