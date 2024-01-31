/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:01:22 by rmidou            #+#    #+#             */
/*   Updated: 2024/01/31 15:16:32 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *ucontent)
{
	static int	bit;
	static char	c;

	(void)ucontent;
	if (bit == 0)
	{
		bit = 0b10000000;
		c = 0;
	}
	if (signum == SIGUSR1)
		c |= bit;
	bit >>= 1;
	if (bit == 0 && c)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	kill(info->si_pid, SIGUSR2);
}

void	config_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("SERVER PID = %d\n", pid);
	while (1)
		config_signals();
	return (SUCCESS);
}
