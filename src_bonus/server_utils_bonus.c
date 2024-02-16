/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:04:57 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/13 11:02:42 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	build_bits(int signal, t_data *lst)
{
	char	current_char_cpy;
	int		size_cpy;

	current_char_cpy = lst->current_char;
	size_cpy = lst->size;
	if (!(lst->start))
	{
		if (signal == SIGUSR1)
			size_cpy = size_cpy << 1 | 1;
		else if (signal == SIGUSR2)
			size_cpy = size_cpy << 1;
	}
	else
	{
		if (signal == SIGUSR1)
			current_char_cpy = (current_char_cpy << 1) | 1;
		else if (signal == SIGUSR2)
			current_char_cpy = current_char_cpy << 1;
		lst->current_char = current_char_cpy;
	}
	lst->size = size_cpy;
}

void	create_string(t_data *lst)
{
	int		size_cpy;
	int		i;

	size_cpy = lst->size;
	i = 0;
	lst->received_string = malloc(sizeof(char) * (size_cpy + 1));
	if (!(lst->received_string))
	{
		reset(lst);
		handle_exit(1, MEMORY_ERROR);
	}
	while (i < size_cpy)
	{
		lst->received_string[i] = 0;
		i++;
	}
	lst->received_string[i] = '\0';
	lst->start = 1;
	lst->bit = 0;
}

void	build_string(t_data *lst)
{
	int	cursor_cpy;

	cursor_cpy = lst->cursor;
	lst->received_string[cursor_cpy] = lst->current_char;
	cursor_cpy++;
	lst->cursor = cursor_cpy;
	lst->current_char = 0;
	lst->bit = 0;
}

void	success(t_data *lst, int *pid)
{
	int	pid_cpy;

	pid_cpy = *pid;
	reset(lst);
	lst->current_char = 0;
	kill_management(pid_cpy, SIGUSR2, lst);
	ft_printf("Message received\n");
	ft_printf("Result : %s\n", lst->received_string);
	free(lst->received_string);
	lst->received_string = NULL;
}
