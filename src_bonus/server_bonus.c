/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:35:21 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/13 11:02:41 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handle_signal(int signal, siginfo_t *info, void	*context)
{
	static t_data	lst = {0};

	(void)context;
	if (!lst.start)
	{
		build_bits(signal, &lst);
		if (lst.bit == 31)
			create_string(&lst);
	}
	else
	{
		build_bits(signal, &lst);
		if (lst.bit == 8)
			build_string(&lst);
		if (lst.cursor == lst.size)
		{
			success(&lst, &info->si_pid);
			return ;
		}
	}
	lst.bit += 1;
	kill_management(info->si_pid, SIGUSR1, &lst);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID : %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
