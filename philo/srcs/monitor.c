/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:57:43 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 10:33:14 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_meals_eaten(t_data *monitor)
{
    int     count;
    int     max_reached;
    t_philo *curr_philo;

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
        pthread_mutex_lock(monitor->m_end);
        monitor->end_flag = 1;
        pthread_mutex_unlock(monitor->m_end);
        return (1);
    }
    return (0);
}


int check_death(t_data *monitor)
{
    int     count;
    t_philo *curr_philo;

    count  = 0;
    while (count  < monitor->number_of_philo)
    {
        curr_philo = &(monitor->philo[count]);
        if ((get_exact_time() - curr_philo->timestamp_last_meal)
            == monitor->time_to_die)
        {
            print_formatter(RED_TEXT "died" RESET_TEXT, curr_philo);
            pthread_mutex_lock(monitor->m_end);
            monitor->end_flag = 1;
            pthread_mutex_unlock(monitor->m_end);
            return (1);
        }
        count++ ;
    }
    return (0);
}


void	*monitoring(void *data)
{
	t_data  *monitor;

    monitor = (t_data *)data;
    while (1)
    {
        if (check_meals_eaten(monitor))
            return (NULL);
        if (check_death(monitor))
            return (NULL);
        usleep(1000); 
    }
    return (NULL);
}
