/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:57:00 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/06/17 06:00:37 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"
# define ERR_INVALID_USAGE 2
# define ERR_INVALID_PID 3
# define ERR_SEND_SIGNAL 4
# define ERR_TIMEOUT 5

extern volatile sig_atomic_t	g_sig;

// client_sigaction.c
void	set_client_sigaction(void);
void	client_handler(int sig);
// client_utils.c
void	validate(int ac, char *av[]);
// client_send_str.c
void	send_str(pid_t srv_pid, char *str);

#endif /* CLIENT_H */