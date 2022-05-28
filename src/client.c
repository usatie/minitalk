/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:11 by susami            #+#    #+#             */
/*   Updated: 2022/05/28 14:48:53 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"

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

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 100 || pid > 99998)
	{
		ft_printf("[%s] is not valid pid(100~99998).\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (*argv[2])
		send_msg(pid, argv[2]);
	return (EXIT_SUCCESS);
}
