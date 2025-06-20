/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 03:07:37 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/17 05:24:28 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_char(pid_t srv_pid, char c);
static void	wait_ack(pid_t srv_pid);
static void	send_bit(pid_t srv_pid, int bit);

void	send_str(pid_t srv_pid, char *str)
{
	while (*str)
		send_char(srv_pid, *str++);
	send_char(srv_pid, '\0');
	return ;
}

static void	send_char(pid_t srv_pid, char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> (7 - i)) & 1;
		g_sig = 0;
		send_bit(srv_pid, bit);
		wait_ack(srv_pid);
		i++;
	}
}

static void	wait_ack(pid_t srv_pid)
{
	int	i;

	i = 0;
	while (g_sig == 0 && i++ < 1000)
		usleep(500);
	if (g_sig == 0)
	{
		ft_printf("[ERROR]Server PID: %d doesn't respond.\n", srv_pid);
		exit(ERR_TIMEOUT);
	}
	return ;
}

static void	send_bit(pid_t srv_pid, int bit)
{
	int	rev;

	if (bit == 0)
		rev = kill(srv_pid, SIGUSR1);
	else
		rev = kill(srv_pid, SIGUSR2);
	if (rev == -1)
	{
		ft_printf("[ERROR] Failed to send signal to PID %d.\n", srv_pid);
		exit(ERR_SEND_SIGNAL);
	}
	return ;
}
