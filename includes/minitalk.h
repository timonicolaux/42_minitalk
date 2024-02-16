/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:02:37 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/13 08:42:19 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define _GNU_SOURCE

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include "../ft_printf/includes/ft_printf.h"

# define SUCCESS_MSG "Message sent"
# define SIGNAL_ERROR "Error during signal exchange"
# define WRONG_PID "Wrong PID format"
# define WRONG_ARG "Please enter two arguments : PID and text"
# define MEMORY_ERROR "Error allocating memory"

typedef struct s_data
{
	char	current_char;
	char	*received_string;

	int		bit;
	int		start;
	int		cursor;
	int		size;
}	t_data;

void	send_signal(int pid, char *str);
void	send_len(int pid, char *str);
void	received(int signal, siginfo_t *info, void	*context);

void	handle_signal(int signal, siginfo_t *info, void	*context);
void	build_bits(int signal, t_data *lst);
void	create_string(t_data *lst);
void	build_string(t_data *lst);
void	success(t_data *lst, int *pid);

void	kill_management(int pid, int signal, t_data *lst);
void	handle_exit(int error, char *msg);
void	reset(t_data *lst);

#endif
