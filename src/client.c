/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:11 by susami            #+#    #+#             */
/*   Updated: 2022/05/29 19:01:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_argparse.h"

#ifndef SLEEP_US
# define SLEEP_US 100
#endif

static void	send_msg(pid_t pid, char *msg)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < 8)
		{
			usleep(SLEEP_US);
			if (*msg & (1 << (7 - i)))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i++;
		}
		if (*msg == '\0')
			return ;
		msg++;
	}
}

static void	err_exit(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	ft_vdprintf(STDERR_FILENO, format, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		err_exit("Usage: %s pid message\n", argv[0]);
	pid = ft_argparse_int(argv[1], 0, "pid");
	if (pid < 100 || pid > 99998)
		err_exit("[%s] is not valid pid(100~99998).\n", argv[1]);
	if (*argv[2])
		send_msg(pid, argv[2]);
	return (EXIT_SUCCESS);
}
