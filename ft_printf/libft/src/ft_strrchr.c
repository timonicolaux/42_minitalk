/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:43:25 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/07 08:11:30 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr_lib(char *s, int c)
{
	int		i;
	char	*str;
	char	car;

	str = (char *)s;
	car = (char)c;
	i = ft_strlen(str);
	while (str[i] != car && i > 0)
		i--;
	if (str[i] == car)
		return (&str[i]);
	else
		return (0);
}
