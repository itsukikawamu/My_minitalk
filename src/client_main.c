/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:01:40 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/18 20:38:03 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_sig = 0;

int	main(int ac, char *av[])
{
	pid_t	srv_pid;
	char	*str;

	validate(ac, av);
	srv_pid = ft_atoi(av[1]);
	str = av[2];
	set_client_sigaction();
	ft_printf("Client PID: %d\n", getpid());
	send_str(srv_pid, str);
	ft_printf("-- Message sent successfully --\n");
	return (0);
}
