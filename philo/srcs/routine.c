/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/04 10:58:04 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eating(t_philo *curr)
{
	print_formatter("has taken right fork", curr);
    print_formatter("has taken left fork", curr);
	curr->timestamp_last_meal = get_exact_time();
	curr->meals_eaten++;
	print_formatter("is eating", curr);
	ft_usleep(curr->time_to_eat, curr); //Need to make sure the forks picked up are lock during this time
	return (0);
}

void	*routine(void *current_philo)
{
	t_philo *curr;
	
	curr = (t_philo *)current_philo;
	while (!(*curr->end_flag))
	{
		eating(curr);
		if (!(*curr->end_flag))
			print_formatter("is sleeping", curr);
		if (!(*curr->end_flag))
		{
			ft_usleep(curr->time_to_sleep, curr);
			print_formatter("is thinking", curr);
		}
	}
	return (NULL);
}
