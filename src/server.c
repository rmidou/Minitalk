/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:01:22 by rmidou            #+#    #+#             */
/*   Updated: 2024/01/13 14:04:49 by rmidou           ###   ########.fr       */
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
		if (kill(info->si_pid, SIGUSR1) == -1)
			exit_handler("Failed to send SIGUSR1 to client");
		return ;
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
		exit_handler("Failed to send SIGUSR2 to client");
}

void	config_signals(void)
{
	struct sigaction	info;

	ft_bzero(&info, sizeof(info));
	info.sa_flags = SA_SIGINFO;
	info.sa_sigaction = &sig_handler;
	if (sigaction(SIGUSR1, &info, NULL) == -1)
		exit_handler("Failed to change SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &info, NULL) == -1)
		exit_handler("Failed to change SIGUSR2's behavior");
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
