/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:50 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/18 20:58:15 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_atm	g_cli = {0};

static void	print_ascii(void);
static void	send_ack(void);
static void	wait_client(void);

int	main(void)
{
	print_ascii();
	ft_printf("Server PID: %d\n", getpid());
	set_server_sigaction();
	while (1)
	{
		wait_client();
		process_signal();
		g_cli.sig = 0;
		send_ack();
	}
	return (0);
}

static void	wait_client(void)
{
	int	i;

	if (g_cli.continued == 1)
	{
		i = 0;
		while (g_cli.sig == 0 && i++ < 100)
			usleep(200);
		if (g_cli.sig == 0)
		{
			ft_printf("\n[ERROR]Server PID: %d doesn't respond.\n", g_cli.pid);
			g_cli.continued = 0;
		}
	}
	if (g_cli.continued == 0)
	{
		while (g_cli.sig == 0)
			usleep(200);
	}
	return ;
}

static void	send_ack(void)
{
	kill(g_cli.pid, SIGUSR1);
}

static void	print_ascii(void)
{
	ft_printf("::::    ::::  ::::::::::: ::::    ::: ::::::::::: ::::::::::"\
		"      :::     :::        :::    :::\n+:+:+: :+:+:+     :+:     :+:"\
		"+:   :+:     :+:         :+:       :+: :+:   :+:        :+:   :+:"\
		"\n+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+         +:+      +"\
		":+   +:+  +:+        +:+  +:+\n+#+  +:+  +#+     +#+     +#+ +:+ +"\
		"#+     +#+         +#+     +#++:++#++: +#+        +#++:++\n+#+    "\
		"   +#+     +#+     +#+  +#+#+#     +#+         +#+     +#+     +#+"\
		" +#+        +#+  +#+\n#+#       #+#     #+#     #+#   #+#+#     #+"\
		"#         #+#     #+#     #+# #+#        #+#   #+#\n###       ### "\
		"########### ###    #### ###########     ###     ###     ### ######"\
		"#### ###    ###\n\n");
}
