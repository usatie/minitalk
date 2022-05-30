/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:54:39 by susami            #+#    #+#             */
/*   Updated: 2022/05/30 11:10:00 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INT_MAX
#include <limits.h>
#include "libft.h"
#include "ft_printf.h"

void	print(t_fmt *fmt, char *str, size_t len);

void	printf_c(t_fmt *fmt, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	(fmt->format)++;
	print(fmt, &c, 1);
}

static size_t	ft_strnlen(char *str, size_t n)
{
	size_t	cnt;

	cnt = 0;
	while (*str && cnt < n)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

void	printf_s(t_fmt *fmt, va_list ap)
{
	char	*s;
	size_t	len;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	(fmt->format)++;
	if ((fmt->flags & PRECISION_FLG))
		len = ft_strnlen(s, fmt->precision);
	else
		len = ft_strlen(s);
	if (len > INT_MAX)
		fmt->out_size = -1;
	print(fmt, s, len);
}
