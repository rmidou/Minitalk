/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:45:04 by rmidou            #+#    #+#             */
/*   Updated: 2024/01/13 14:15:04 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_handler(char *msg)
{
	ft_putstr_fd("\nError: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(FAILURE);
}

void	verify_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		exit_handler("Please use: ./client <server_pid> <message>");
	while (ft_isdigit(av[1][i]))
		i++;
	if (av[1][i])
		exit_handler("Wrong pid");
	if (av[2][0] == '\0')
		exit_handler("Empty message");
}
