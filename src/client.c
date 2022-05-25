/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:22:11 by susami            #+#    #+#             */
/*   Updated: 2022/05/25 22:02:42 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
// TODO: remove
#include <stdlib.h>

#ifndef SLEEP_US
# define SLEEP_US 20
#endif

static void	send_msg(pid_t pid, char *msg)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < 8)
		{
			if (*msg & (1 << (7 - i)))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i++;
			usleep(SLEEP_US);
		}
		if (*msg == '\0')
			return ;
		msg++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	// TODO: strtol
	send_msg(strtol(argv[1], NULL, 10), argv[2]);
	return (0);
}
