/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 15:37:29 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_exact_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(int time_to_wait)
{
	int	time;
	int	start;

	start = get_exact_time() + time_to_wait;
	time = get_exact_time();
	while (time < start)
	{
		usleep(500);
		time = get_exact_time();
	}
	return (0);
}

int	print_formatter(char *str, t_philo *curr)
{
	pthread_mutex_lock(curr->m_printf);
    printf("%d %d %s\n", get_exact_time() - curr->birth_time, curr->philo_id, str);
	pthread_mutex_unlock(curr->m_printf);
	return (0);
}

int		eating(t_philo *curr)
{
	print_formatter("has taken right fork", curr);
    print_formatter("has taken left fork", curr);
	print_formatter("is eating", curr);
	ft_usleep(curr->time_to_eat); //Need to make sure the forks picked up are lock during this time
	return (0);
}

void	*routine(void *current_philo)
{
	t_philo *curr = (t_philo *)current_philo;

	eating(curr);
	print_formatter("is sleeping", curr);
	ft_usleep(curr->time_to_sleep); // no need to mutex, several philo can sleep together
	print_formatter("is thinking", curr);

    return (NULL);
}
