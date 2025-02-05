/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:11 by omaezzem          #+#    #+#             */
/*   Updated: 2025/02/05 11:57:59 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

static	void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(600);
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

int main(int ac, char **av)
{
    pid_t   pid;
    int     i;

    i = 0;
    if (ac == 3 && av[2][0] != '\0')
    {
		pid = validate_pid(av[1]);
		if (pid <= 0)
		{
    		ft_putstr_fd(RED "Invalid PID\n", 2);
    		return (1);
		}
        while (av[2][i] != '\0')
        {
            send_char(pid, av[2][i]);
            i++;
        }
		send_char(pid,'\0');
    }
    else
    {
        ft_putstr_fd(RED "Error: Invalid number of arguments.\n", 2);
        ft_putstr_fd(RED "Usage: ./client <server_pid> <message>\n", 2);
    }
}
