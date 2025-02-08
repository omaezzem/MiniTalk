/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:23:46 by omaezzem          #+#    #+#             */
/*   Updated: 2025/02/08 11:31:44 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

static void	received_bit(int signal, siginfo_t *info, void *context)
{
	static int	bits;
	static char	byte;
	static int	previous_pid;

	(void)context;
	if (previous_pid != info->si_pid)
	{
		previous_pid = info->si_pid;
		bits = 0;
		byte = 0;
	}
	byte = byte << 1;
	if (signal == SIGUSR2)
		byte |= 1;
	bits++;
	if (bits == 8)
	{
		if (byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		bits = 0;
		byte = 0;
	}
}

void	action(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = received_bit;
	if (sigaction(SIGUSR1, &sig, NULL) == -1
		|| sigaction(SIGUSR2, &sig, NULL) == -1)
		exit(1);
}

int	main(int ac, char **av)
{
	int					pid;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd(RED "Error: Invalid number of arguments.:(\n", 2);
		ft_putstr_fd(RED "Usage: ./server <server_pid> <message>\n", 2);
		return (0);
	}
	pid = getpid();
	ft_putstr_fd(YLW "PID->", 1);
	ft_putnbr_fd(pid, 1);
	write (1, "\n", 1);
	ft_putstr_fd(GRAY "waiting for a message...\n", 1);
	action();
	while (1)
		pause();
	return (0);
}
