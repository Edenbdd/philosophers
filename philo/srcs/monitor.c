/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:57:43 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/04 10:34:16 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//DIVIDE IN 2 OR 3
void	*monitoring(void *data)
{
	t_data  *monitor;
    t_philo *curr_philo;
    int     count;
    int     max_reached;

    monitor = (t_data *)data;
    while (1)
    {
        count = 0;
        max_reached = 0;
        while (monitor->max_nb_of_meals != -2 
                && count < monitor->number_of_philo)
        {
            curr_philo = &(monitor->philo[count]);
            if (curr_philo->meals_eaten >= monitor->max_nb_of_meals)
                max_reached++;
            count++ ;
        }
        if (count  != 0 && max_reached == count)
        {
            dprintf(STDERR_FILENO, "end flag raised\n");
            monitor->end_flag = 1;
        }
        count  = 0;
        while (count  < monitor->number_of_philo)
        {
            curr_philo = &(monitor->philo[count]);
            if ((get_exact_time() - curr_philo->timestamp_last_meal)
                == monitor->time_to_die)
                monitor->end_flag = 1;
            count++ ;
        }
        if (monitor->end_flag)
            break;
        usleep(1000); 
    }
    return (NULL);
}
