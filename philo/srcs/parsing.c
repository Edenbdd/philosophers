/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:56:52 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/04 10:29:05 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int only_digit_sign(char *arg)
{
    int pos;

    pos = 0;
    while (arg[pos])
    {
        if ((arg[pos] < '0' || arg[pos] > '9')
            && arg[pos] != '+' && !is_space(arg[pos]))
            return (0);
        pos++;
    }
    return (1);
}

long long	ft_atoll(char *str)
{
	int			pos;
	int			sign;
	long long	result;

	pos = 0;
	sign = 1;
	result = 0;
	while (str[pos] && is_space(str[pos]))
		pos++;
	if (str[pos] == '+')
		pos++;
    while (str[pos] == '0')
    {    pos++;}
	while (str[pos] && is_space(str[pos]))
		pos++;
	while (str[pos] && !is_space(str[pos]))
	{
		result *= 10;
		result += str[pos] - 48;
		pos++;
	}
	return (result * sign);
}

int	too_big(long long nb)
{
	int	half_a;
	int	half_b;

	half_a = nb / 2;
	half_b = nb - half_a;
	if (half_a < 0 && half_b < 0 && half_a + half_b > 0)
		return (-1);
	if (half_a > 0 && half_b > 0 && half_a + half_b < 0)
		return (-1);
	return (0);
}

int parsing(char *arg)
{
    long long   lnb;
    
    if (!only_digit_sign(arg))
        return (-1);
    lnb = ft_atoll(arg);
	if (too_big(lnb))
	   	return (-1);
    return ((int)lnb);
}
