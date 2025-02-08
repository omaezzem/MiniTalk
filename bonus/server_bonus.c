/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:33:04 by omaezzem          #+#    #+#             */
/*   Updated: 2025/02/08 11:27:42 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk_bonus.h"

int	check_uni_bytes(unsigned char c)
{
	if (c < 128)
		return (1);
	else if ((c & 0b11100000) == 0b11000000)
		return (2);
	else if ((c & 0b11110000) == 0b11100000)
		return (3);
	else if ((c & 0b11111000) == 0b11110000)
		return (4);
	return (0);
}

int	process_char(int *bits, char *byte, int *cpid, int *pos)
{
	static unsigned char	utf8_buf[4];
	static int				remaining;

	if (++(*bits) == 8)
	{
		if (*pos == 0)
			remaining = check_uni_bytes(*byte);
		utf8_buf[(*pos)++] = *byte;
		if (--remaining == 0)
		{
			utf8_buf[*pos] = '\0';
			ft_putstr_fd((char *)utf8_buf, 1);
			*pos = 0;
			kill(*cpid, SIGUSR1);
		}
		if (*byte == '\0')
		{
			kill(*cpid, SIGUSR2);
			write(1, "\n", 1);
		}
		*bits = 0;
		*byte = 0;
	}
	return (0);
}

static void	received_bit(int signal, siginfo_t *info, void *context)
{
	static int		bits;
	static char		byte;
	static int		pos;
	static pid_t	cpid;

	bits = 0;
	byte = 0;
	pos = 0;
	(void)context;
	if (cpid != info->si_pid)
	{
		cpid = info->si_pid;
		bits = 0;
		byte = 0;
		pos = 0;
	}
	byte = (byte << 1);
	if (signal == SIGUSR2)
		byte |= 1;
	process_char(&bits, &byte, (int *)&cpid, &pos);
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
	int	pid;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd(RED "Error: Invalid number of arguments.:(\n", 2);
		ft_putstr_fd(RED "Usage: ./server_bonus\n", 2);
		return (0);
	}
	pid = getpid();
	ft_putstr_fd(YLW "PID->", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	ft_putstr_fd(GRAY "waiting for a message...\n", 1);
	action();
	while (1)
		pause();
	return (0);
}
