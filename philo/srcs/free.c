/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:49:45 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 14:22:24 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_data *data)
{
	if (pthread_mutex_destroy(data->m_printf))
		return (-1);
	free(data->m_printf);
	return (0);
}


int free_destroy_all(t_data *data)
{
    int     i;
    t_philo *current;
    if (destroy_mutex(data))
        return (-1);
    free(data->m_printf);
    i = 0;
    while (i < data->number_of_philo)
    {
        current = &data->philo[i];
        free(&(current->philo));
        i++;
    }
    free(data->philo);
    return (0);
}
