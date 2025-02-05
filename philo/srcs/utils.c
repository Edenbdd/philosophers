/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:56:53 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 14:52:33 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Gettimeofday but in milliseconds*/
int	get_exact_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*Modified usleep for more precision*/
int	ft_usleep(int time_to_wait, t_philo *curr)
{
	int	time;
	int	start;

	(void)curr;
	start = get_exact_time() + time_to_wait;
	time = get_exact_time();
	while (time < start)
	{
		usleep(500);
		time = get_exact_time();
	}
	return (0);
}

/*Display the messages recording the philosophers actions*/
int	print_formatter(char *str, t_philo *curr)
{
	pthread_mutex_lock(curr->m_end);
	if (!(*curr->end_flag))
	{
		pthread_mutex_lock(curr->m_printf);
		printf("%d %d %s\n", get_exact_time() - curr->birth_time,
			curr->philo_id, str);
		pthread_mutex_unlock(curr->m_printf);
	}
	pthread_mutex_unlock(curr->m_end);
	return (0);
}

/*Display error message in case of parsing error*/
int	wrong_arg_msg(void)
{
	char	*msg;
	int		len;

	msg = "Wrong arguments.\nExpected input:\n(positive int only)\n\
			unsigned in number_of_philosophers\n\
			time_to_die\n\
			time_to_eat\n\
			time_to_sleep\n\
			optional: number_of_times_each_philosopher_must_eat\n";
	len = 0;
	while (msg[len])
		len++;
	write(STDERR_FILENO, msg, len);
	return (-1);
}

/*Handle when there is only 1 philo*/
int	lonely_death(t_philo *curr)
{
	print_formatter("has taken a fork", curr);
	print_formatter("died", curr);
	return (0);
}
