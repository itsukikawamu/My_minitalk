/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:57:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/17 06:01:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define BUF_SIZE 4096

typedef struct s_atm
{
	volatile sig_atomic_t	sig;
	volatile sig_atomic_t	pid;
	volatile sig_atomic_t	continued;
}	t_atm;

extern t_atm	g_cli;

// server_sigaction.c
void	set_server_sigaction(void);
void	server_action(int sig, siginfo_t *info, void *ctx);
// server_process_signal.c
void	process_signal(void);

#endif /* SERVER_H */