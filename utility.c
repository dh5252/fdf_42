/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:14:59 by cahn              #+#    #+#             */
/*   Updated: 2023/08/08 20:16:06 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    print_error_exit(char *err)
{
    int i;

    i = 0;
    while (err[i])
        ++i;
    write(1, err, i);
    exit(1);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;
	int	num;

	i = 0;
	minus = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num * minus);
}
