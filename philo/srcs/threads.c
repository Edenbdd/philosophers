/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:31 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 13:31:29 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Create and join the threads*/

#include "philo.h"

/*Creates the even and uneven philosophers thread*/
int	philo_generator(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		if (pthread_create(&(current_philo->philo_thread), NULL, &routine,
				current_philo))
			return (-1);
		i += 2;
	}
	i = 1;
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		if (pthread_create(&(current_philo->philo_thread), NULL, &routine,
				current_philo))
			return (-1);
		i += 2;
	}
	return (0);
}

/*Create and join threads, including the butler*/
int	thread_setup(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	if (data->number_of_philo > 1)
		pthread_create(&(data->butler), NULL, &monitoring, data);
	if (philo_generator(data))
		return (-1);
	i = 0;
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		pthread_join(current_philo->philo_thread, NULL);
		i++;
	}
	if (data->number_of_philo > 1)
		pthread_join(data->butler, NULL);
	return (0);
}
