/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:11 by susami            #+#    #+#             */
/*   Updated: 2022/05/29 18:58:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_argparse.h"

typedef struct s_ack {
	volatile sig_atomic_t	flg;
	int						pid;
}	t_ack;

static t_ack	g_ack;

static void	send_msg(pid_t pid, char *msg)
{
	int	i;

	g_ack.flg = 1;
	while (1)
	{
		i = 0;
		while (i < 8)
		{
			while (!g_ack.flg)
				pause();
			g_ack.flg = 0;
			usleep(10);
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

// sometimes si_pid becomes 0 even though it is come from server...
/*
 * if (siginfo->si_pid == g_ack.pid)
 * 		g_ack.flg = 1
 */
static void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	if (siginfo->si_pid == g_ack.pid || siginfo->si_pid == 0)
		g_ack.flg = 1;
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
	struct sigaction	act;

	if (argc != 3)
		err_exit("Usage: %s pid message\n", argv[0]);
	g_ack.pid = ft_argparse_int(argv[1], 0, "g_ack.pid");
	if (g_ack.pid < 100 || g_ack.pid > 99998)
		err_exit("[%s] is not valid pid(100~99998).\n", argv[1]);
	if (*argv[2])
	{
		act.sa_sigaction = handler;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &act, NULL) < 0)
			err_exit("sigaction error");
		send_msg(g_ack.pid, argv[2]);
	}
	return (EXIT_SUCCESS);
}
