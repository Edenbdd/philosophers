/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 13:11:25 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*When philo_id is uneven*/
int	uneven_routine(t_philo *curr)
{
	while (1)
	{
		pthread_mutex_lock(curr->m_end);
		if (!(*curr->end_flag))
		{
			pthread_mutex_unlock(curr->m_end);
			if (eating(curr))
				return (1);
			print_formatter("is sleeping", curr);
			ft_usleep(curr->time_to_sleep, curr);
			print_formatter("is thinking", curr);
		}
		else
		{
			pthread_mutex_unlock(curr->m_end);
			return (1);
		}
	}
	return (0);
}

/*When philo_id is even*/
int	even_routine(t_philo *curr)
{
	while (1)
	{
		pthread_mutex_lock(curr->m_end);
		if (!(*curr->end_flag))
		{
			pthread_mutex_unlock(curr->m_end);
			print_formatter("is thinking", curr);
			if (eating(curr))
				return (1);
			print_formatter("is sleeping", curr);
			ft_usleep(curr->time_to_sleep, curr);
		}
		else
		{
			pthread_mutex_unlock(curr->m_end);
			return (1);
		}
	}
	return (0);
}

/*Main routine function*/
void	*routine(void *current_philo)
{
	t_philo *curr;
	
	curr = (t_philo *)current_philo;
	if (curr->number_of_philo == 1)
		lonely_death(curr);
	if (curr->philo_id % 2)
		uneven_routine(curr);
	else
		even_routine(curr);
	return (NULL);
}
