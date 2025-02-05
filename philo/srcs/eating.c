/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:50:56 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 12:54:54 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Handling fork for even philo_id*/
int	even_forks(t_philo *curr, int right_fork_id, int left_fork_id)
{
	pthread_mutex_lock(&curr->m_forks[right_fork_id]);
	if (print_formatter("has taken a fork", curr))
	{
		pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
		return (1);
	}
	pthread_mutex_lock(&curr->m_forks[left_fork_id]);
	if (print_formatter("has taken a fork", curr))
	{
		pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
		pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
		return (1);
	}
	return (0);
}

/*Function handling forks (for uneven and redirect even)*/
int	picking_forks(t_philo *curr, int right_fork_id, int left_fork_id)
{
	if (curr->philo_id % 2)
	{
		if (even_forks(curr, right_fork_id, left_fork_id))
			return (1);
	}
	else
	{
		pthread_mutex_lock(&curr->m_forks[left_fork_id]);
		if (print_formatter("has taken a fork", curr))
		{
			pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
			return (1);
		}
		pthread_mutex_lock(&curr->m_forks[right_fork_id]);
    	if (print_formatter("has taken a fork", curr))
		{
			pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
			pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
			return (1);
		}
	}
	return (0);
}

/*Main function handling eating*/
int		eating(t_philo *curr)
{
	int	right_fork_id;
	int	left_fork_id;

	right_fork_id = curr->philo_id - 1;
	if (curr->philo_id == 1)
		left_fork_id = curr->number_of_philo - 1;
	else
		left_fork_id = curr->philo_id - 2;
	if (picking_forks(curr, right_fork_id, left_fork_id))
		return (1);
	pthread_mutex_lock(curr->m_eating);
	curr->timestamp_last_meal = get_exact_time();
	curr->meals_eaten++;
	pthread_mutex_unlock(curr->m_eating);
	if (print_formatter("is eating", curr))
	{
		pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
		pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
		return (1);
	}
	ft_usleep(curr->time_to_eat, curr);
	pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
	pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
	return (0);
}
