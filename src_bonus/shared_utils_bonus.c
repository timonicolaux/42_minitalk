/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:00:22 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/13 11:02:44 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	kill_management(int pid, int signal, t_data *lst)
{
	if (kill(pid, signal) != 0)
	{
		ft_printf("Error : kill failed or wrong PID\n");
		if (lst && lst->received_string)
		{
			free(lst->received_string);
			lst->received_string = NULL;
		}
		if (signal == SIGUSR1)
			reset(lst);
		exit(EXIT_FAILURE);
	}
}

void	handle_exit(int error, char *msg)
{
	ft_printf("%s\n", msg);
	if (!error)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	reset(t_data *lst)
{
	if (!lst)
		return ;
	lst->start = 0;
	lst->bit = 0;
	lst->cursor = 0;
	lst->size = 0;
}
