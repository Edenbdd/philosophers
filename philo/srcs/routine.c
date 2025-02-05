/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 09:55:54 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	picking_forks(t_philo *curr, int right_fork_id, int left_fork_id)
{
	if (curr->philo_id % 2)
	{
		pthread_mutex_lock(&curr->m_forks[right_fork_id]);
		// dprintf(STDERR_FILENO, RED_TEXT "fork %d locked by %d\n" RESET_TEXT, right_fork_id, curr->philo_id);
		print_formatter("has taken a fork", curr);
		pthread_mutex_lock(&curr->m_forks[left_fork_id]);
		//dprintf(STDERR_FILENO, RED_TEXT "fork %d locked by %d\n" RESET_TEXT, left_fork_id, curr->philo_id);
    	print_formatter("has taken a fork", curr);
	}
	else
	{
		pthread_mutex_lock(&curr->m_forks[left_fork_id]);
		// dprintf(STDERR_FILENO, RED_TEXT "fork %d locked by %d\n" RESET_TEXT, left_fork_id, curr->philo_id);
    	print_formatter("has taken a fork", curr);
		pthread_mutex_lock(&curr->m_forks[right_fork_id]);
		print_formatter("has taken a fork", curr);
		// dprintf(STDERR_FILENO, RED_TEXT "fork %d locked by %d\n" RESET_TEXT, right_fork_id, curr->philo_id);
	}
	return (0);
}

/*add a mutex around eating when I change the data*/
int		eating(t_philo *curr)
{
	int	right_fork_id;
	int	left_fork_id;

	// dprintf(STDERR_FILENO, "%d ready to eat\n", curr->philo_id);
	right_fork_id = curr->philo_id - 1;
	// dprintf(STDERR_FILENO, RED_TEXT "for philo %d right fork is %d\n" RESET_TEXT, curr->philo_id, right_fork_id);
	if (curr->philo_id == 1)
		left_fork_id = curr->number_of_philo - 1;
	else
		left_fork_id = curr->philo_id - 2;
	// dprintf(STDERR_FILENO, RED_TEXT "for philo %d left fork is %d\n" RESET_TEXT, curr->philo_id, left_fork_id);
	picking_forks(curr, right_fork_id, left_fork_id);
	curr->timestamp_last_meal = get_exact_time();
	curr->meals_eaten++;
	print_formatter("is eating", curr);
	ft_usleep(curr->time_to_eat, curr);
	pthread_mutex_unlock(&curr->m_forks[right_fork_id]);
	// dprintf(STDERR_FILENO, RED_TEXT "fork %d UNlocked by %d\n" RESET_TEXT, right_fork_id, curr->philo_id);
	pthread_mutex_unlock(&curr->m_forks[left_fork_id]);
	// dprintf(STDERR_FILENO, RED_TEXT "fork %d UNlocked by %d\n" RESET_TEXT, left_fork_id, curr->philo_id);
	return (0);
}

int	lonely_death(t_philo *curr)
{
	print_formatter("has taken a fork", curr);
	print_formatter("died", curr);
	return (0);
}

int	sleeping(t_philo *curr)
{
	print_formatter("is sleeping", curr);
	ft_usleep(curr->time_to_sleep, curr);
	return (0);
}

void	*routine(void *current_philo)
{
	t_philo *curr;
	
	curr = (t_philo *)current_philo;
	if (curr->number_of_philo == 1)
		lonely_death(curr);
	if (curr->philo_id % 2)
	{
		while (!(*curr->end_flag)) //UNEVEN ROUTINE
		{
			eating(curr);
			sleeping(curr);
			print_formatter("is thinking", curr);
		}
		return (NULL);
	}
	while (!(*curr->end_flag)) //EVEN ROUTINE
	{
		print_formatter("is thinking", curr);
		eating(curr);
		sleeping(curr);
	}
	return (NULL);
}
