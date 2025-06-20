/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:54:19 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/17 06:15:22 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	validate(int ac, char *av[])
{
	pid_t	srv_pid;

	if (ac != 3)
	{
		ft_printf("Usage: %s <Server PID> <Stinrg to send>\n", av[0]);
		exit(ERR_INVALID_USAGE);
	}
	srv_pid = ft_atoi(av[1]);
	if (srv_pid <= 0)
	{
		ft_printf("Invalid PID: %d\n", srv_pid);
		exit(ERR_INVALID_PID);
	}
	if (kill(srv_pid, 0) == -1)
	{
		ft_printf("[ERROR]Server PID: %d doesn't exist\n", srv_pid);
		exit(ERR_INVALID_PID);
	}
	return ;
}
