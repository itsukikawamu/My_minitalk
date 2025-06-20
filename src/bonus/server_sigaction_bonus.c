/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sigaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:04:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/17 05:13:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	set_server_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = server_action;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(ERR_SIGACTION);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(ERR_SIGACTION);
	return ;
}

void	server_action(int sig, siginfo_t *info, void *ctx)
{
	if (g_cli.pid != info->si_pid)
	{
		if (g_cli.pid && kill(g_cli.pid, 0) == 0)
			return ;
		g_cli.continued = 0;
	}
	else
		g_cli.continued = 1;
	g_cli.sig = sig;
	g_cli.pid = info->si_pid;
	(void)ctx;
	return ;
}
