/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:35:23 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/13 11:02:36 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_signal(int pid, char *str)
{
	int		bit;
	int		i;

	bit = 7;
	i = 0;
	while (str[i])
	{
		while (bit >= 0)
		{
			if ((str[i] >> bit & 1) == 1)
				kill_management(pid, SIGUSR1, NULL);
			else if ((str[i] >> bit & 1) == 0)
				kill_management(pid, SIGUSR2, NULL);
			usleep(300);
			bit--;
		}
		bit = 7;
		i++;
	}
}

void	send_len(int pid, char *str)
{
	int	bit;
	int	len;

	bit = 31;
	len = ft_strlen((char *)str);
	while (bit >= 0)
	{
		if ((len >> bit & 1) == 1)
			kill_management(pid, SIGUSR1, NULL);
		else if ((len >> bit & 1) == 0)
			kill_management(pid, SIGUSR2, NULL);
		usleep(300);
		bit--;
	}
}

void	received(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
		return ;
	else if (signal == SIGUSR2)
		handle_exit(0, SUCCESS_MSG);
	else
		handle_exit(1, SIGNAL_ERROR);
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = received;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			handle_exit(1, WRONG_PID);
		send_len(pid, av[2]);
		send_signal(pid, av[2]);
		return (0);
	}
	else
		handle_exit(1, WRONG_ARG);
}
