/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_process_signal_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 03:43:54 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/18 20:54:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	output_message(char *buf, int *cnt);
static char	process_bit(char c);

void	process_signal(void)
{
	static char	buf[BUF_SIZE];
	static int	char_cnt;
	static int	bit_cnt;

	if (g_cli.continued == 0)
	{
		char_cnt = 0;
		bit_cnt = 0;
	}
	buf[char_cnt] = process_bit(buf[char_cnt]);
	bit_cnt++;
	if (bit_cnt == 8)
	{
		char_cnt++;
		output_message(buf, &char_cnt);
		bit_cnt = 0;
	}
	return ;
}

static void	output_message(char *buf, int *cnt)
{
	if (buf[*cnt - 1] == '\0')
	{
		write(1, buf, *cnt - 1);
		ft_printf("\n-- Message recieved successfully --\n");
		g_cli.continued = 0;
		*cnt = 0;
		return ;
	}
	if (*cnt == BUF_SIZE)
	{
		write(1, buf, BUF_SIZE);
		*cnt = 0;
	}
	return ;
}

static char	process_bit(char c)
{
	c <<= 1;
	if (g_cli.sig == SIGUSR2)
		c |= 1;
	return (c);
}
