/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:06 by susami            #+#    #+#             */
/*   Updated: 2022/05/27 00:48:37 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_msg {
	char	c;
	int		len;
}	t_msg;

// Sometimes siginfo->si_pid become 0
// even though it is come from client.
// So I reserve the client_pid.
static volatile sig_atomic_t	g_client_pid;

static void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static t_msg	msg;

	(void)ucontext;
	msg.c <<= 1;
	msg.len++;
	if (sig == SIGUSR1)
		msg.c += 1;
	else if (sig == SIGUSR2)
		msg.c += 0;
	if (msg.len == 8)
	{
		if (msg.c != '\0')
			write(STDOUT_FILENO, &msg.c, 1);
		msg.c = 0;
		msg.len = 0;
	}
	if (siginfo->si_pid != 0)
	{
		g_client_pid = siginfo->si_pid;
		kill(siginfo->si_pid, SIGUSR1);
	}
	else
		kill(g_client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("[SERVER] PID is %d\n", getpid());
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) < 0)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &act, NULL) < 0)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
