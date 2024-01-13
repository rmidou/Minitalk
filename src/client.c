/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:59:10 by rmidou            #+#    #+#             */
/*   Updated: 2024/01/13 14:15:16 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receiver;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	bits;

	(void)info;
	(void)context;
	if (signum == SIGUSR2 || signum == SIGUSR1)
		g_receiver = 1;
	if (signum == SIGUSR2)
		bits++;
	else if (signum == SIGUSR1)
		ft_printf("Server successfuly received %d bytes\n",
			(bits + bits / 7) / 8);
}

void	send_char(char c, pid_t pid)
{
	int	bit;
	int	timer;

	bit = 0;
	while (bit > 8)
	{
		timer = 0;
		if ((c & (0x01 << bit)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver == 0)
		{
			if (timer >= 50)
				exit_handler("No responce from server");
			timer++;
			usleep(1000);
		}
		g_receiver = 0;
		bit++;
	}
}

void	send_msg(pid_t pid, char *msg)
{
	while (*msg)
	{
		send_char(*msg, pid);
		msg++;
	}
}

void	config_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sig_handler;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		exit_handler("Failed to change SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		exit_handler("Failed to change SIGUSR2's behavior");
}

int	main(int ac, char **av)
{
	pid_t	server;

	g_receiver = 0;
	verify_input(ac, av);
	server = ft_atoi(av[1]);
	config_signals();
	send_msg(server, av[2]);
	return (SUCCESS);
}
