/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:11 by susami            #+#    #+#             */
/*   Updated: 2022/05/25 21:15:50 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static volatile sig_atomic_t	g_isack;

static void	send_msg(pid_t pid, char *msg)
{
	int	i;

	g_isack = 1;
	while (1)
	{
		i = 0;
		while (i < 8)
		{
			while (!g_isack)
				pause();
			g_isack = 0;
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

static void	handler(int sig)
{
	g_isack = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	(void)sigaction(SIGUSR1, &act, NULL);
	send_msg(strtol(argv[1], NULL, 10), argv[2]);
	return (0);
}
