/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:06 by susami            #+#    #+#             */
/*   Updated: 2022/05/25 22:02:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"

#ifndef BUFSIZE
# define BUFSIZE 10
#endif

typedef struct s_g_msg {
	char	c;
	int		c_len;
	char	buf[BUFSIZE];
	int		len;
}	t_g_msg;

static t_g_msg	g_msg;

static void	handler(int sig)
{
	g_msg.c <<= 1;
	g_msg.c_len++;
	if (sig == SIGUSR1)
		g_msg.c += 1;
	else if (sig == SIGUSR2)
		g_msg.c += 0;
	if (g_msg.c_len == 8)
	{
		g_msg.buf[g_msg.len] = g_msg.c;
		g_msg.len++;
		if (g_msg.c == '\0' || g_msg.len == BUFSIZE)
		{
			write(STDOUT_FILENO, g_msg.buf, g_msg.len);
			g_msg.len = 0;
		}
		g_msg.c = 0;
		g_msg.c_len = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("PID is %d\n", getpid());
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	(void)sigaction(SIGUSR1, &act, NULL);
	(void)sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
