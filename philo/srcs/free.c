/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:49:45 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 13:29:00 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Handle destroying and freeing of mutexes*/
int	destroy_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_destroy(data->m_printf))
		return (-1);
	free(data->m_printf);
	if (pthread_mutex_destroy(data->m_end))
		return (-1);
	free(data->m_end);
	if (pthread_mutex_destroy(data->m_eating))
		return (-1);
	free(data->m_eating);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_destroy(&data->m_forks[i]))
			return (-1);
		i++;
	}
	free(data->m_forks);
	return (0);
}

/*Main free function*/
int	free_destroy_all(t_data *data)
{
	int	i;

	if (destroy_mutex(data))
		return (-1);
	i = 0;
	free(data->philo);
	return (0);
}
