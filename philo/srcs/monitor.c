/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:57:43 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 16:57:42 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_data  *monitor;
    t_philo *curr_philo;
    int     i;
    int     max_reached;

    monitor = (t_data *)data;
    while (1)
    {
        i = 0;
        max_reached = 0;
        while (monitor->max_nb_of_meals != -2 
                && i < monitor->number_of_philo)
        {
            dprintf(2, "i is %d and nb of philo is %d\n", i, monitor->number_of_philo);
            curr_philo = &(monitor->philo[i]);
            if (curr_philo->meals_eaten >= monitor->max_nb_of_meals)
            {
                dprintf(STDERR_FILENO, "philo %d has eaten %d meals on %d\n",
                    i, curr_philo->meals_eaten, monitor->max_nb_of_meals);
                max_reached++;
            }
            i++;
        }
        if (i != 0 && max_reached == i)
            monitor->end_flag = 1;
        i = 0;
        while (i < monitor->number_of_philo)
        {
            curr_philo = &(monitor->philo[i]);
            if ((get_exact_time() - curr_philo->timestamp_last_meal)
                == monitor->time_to_die)
            {
                print_formatter("died", curr_philo);
                monitor->end_flag = 1;
            }
            i++;
        }
        if (monitor->end_flag)
        {
            print_formatter("ended the loop", curr_philo);
            break;
        }
        usleep(1000); 
    }
    return (NULL);
}
