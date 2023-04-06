/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:18:29 by evallee-          #+#    #+#             */
/*   Updated: 2023/03/02 03:26:59 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
• Your function has to handle the following conversions: cspdiuxX%

You have to implement the following conversions:
* %c Prints a single character.
* %s Prints a string (as defined by the common C convention).
* %p The void * pointer argument has to be printed in hexadecimal format.
* %d Prints a decimal (base 10) number.
* %i Prints an integer in base 10.
* %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
* %% Prints a percent sign.
*/

#include "libft.h"

static int	ft_writearg(va_list *args, char c)
{
	if (!c)
		return (0);
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*args, char *), 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(*args, int), 1));
	if (c == 'u')
		return (ft_putuint_fd(va_arg(*args, unsigned int), 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	if (c == 'x')
		return (ft_puthex_fd((uint32_t)va_arg(*args, int), false, 1));
	if (c == 'X')
		return (ft_puthex_fd((uint32_t)va_arg(*args, int), true, 1));
	if (c == 'p')
		return (ft_putaddr_fd(va_arg(*args, void *), 1));
	return (0);
}

int	ft_printf(const char *f, ...)
{
	va_list			args;
	int				len;
	char			ct;

	len = 0;
	va_start(args, f);
	while (*f)
	{
		ct = *f++;
		if (ct != '%')
			len += write(1, &ct, 1);
		else
			len += ft_writearg(&args, *f++);
	}
	va_end(args);
	return (len);
}
