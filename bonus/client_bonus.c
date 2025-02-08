/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:15:05 by omaezzem          #+#    #+#             */
/*   Updated: 2025/02/08 18:19:33 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk_bonus.h"

void	ack_received(int sig)
{
	(void)sig;
}

static void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(250);
		usleep(250);
		i--;
	}
}

int	validate_pid(char *av_pid)
{
	int	i;
	int	pid;

	i = 0;
	while (av_pid[i])
	{
		if (!(av_pid[i] >= '0' && av_pid[i] <= '9'))
		{
			ft_putstr_fd(RED "PID not working\n", 2);
			return (0);
		}
		i++;
	}
	pid = ft_atoi(av_pid);
	if (pid <= 0)
	{
		ft_putstr_fd(RED "PID not positive\n", 2);
		return (0);
	}
	return (pid);
}

void	ac_error(void)
{
	ft_putstr_fd (RED "Error: Invalid number of arguments.\n", 2);
	ft_putstr_fd (RED "Usage: ./client_bonus <server_pid> <message>\n", 2);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	signal (SIGUSR1, ack_received);
	signal (SIGUSR2, ack_received);
	if (ac == 3 && av[2][0] != '\0')
	{
		pid = validate_pid(av[1]);
		if (pid <= 0)
		{
			ft_putstr_fd(RED "Invalid PID\n", 2);
			return (1);
		}
		i = 0;
		while (av[2][i] != '\0')
		{
			send_char(pid, av[2][i]);
			i++;
		}
		send_char(pid, '\0');
		ft_putstr_fd(GRN "Message sent successfully ✅\n", 1);
	}
	else
		ac_error();
}
