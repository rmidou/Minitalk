/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:03:37 by rmidou            #+#    #+#             */
/*   Updated: 2024/01/13 14:15:08 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <libft.h>
# include <unistd.h>
# include <signal.h>

# define SUCCESS 0
# define FAILURE -1

void	exit_handler(char *msg);
void	verify_input(int ac, char **av);

#endif