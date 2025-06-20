/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sigaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:33:32 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/21 02:17:17 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void	set_client_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_handler = client_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(ERR_SIGACTION);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(ERR_SIGACTION);
	return ;
}

void	client_handler(int sig)
{
	g_sig = sig;
	return ;
}
